#include "qcrawler_get_task.h"
#include "qcrawler_util.h"
#include "qcrawler_sleep.h"
//#include "unistd.h"
#include <iostream>

void QCrawlerGetTask::process(bool r, QCrawlerRecord &rec) {
    if (!r) {
        return;
    }

    static int first_time = true;

    if (first_time) {
        first_time = false;

        std::string url;
        while (std::cin >> url) {
            QUrl qurl(QString::fromUtf8(url.c_str()));
            if (qurl.isValid()) {
                QCrawlerUrl c_url;
                std::string host = qurl.host().toUtf8().constData();
                if (host.size() < 1) {
                    continue;
                }

                c_url.set_url(qurl.toString().toUtf8().constData());
                c_url.set_crawl_level(0);
                c_url.set_host(host);
                c_url.set_crawl_type(QCrawlerUrl::HOST_RESTRICTED);
                //c_url.set_crawl_type(QCrawlerUrl::UPDATE);
                std::string s_str;
                c_url.SerializeToString(&s_str);
                url_queue->push(host, s_str);
            }
        }
    }

    QCrawlerUrl* crawl_url = rec.mutable_crawl_url();
    std::string serial_str;
    if (url_queue->shift(&serial_str)) {
        crawl_url->ParseFromString(serial_str);
    } else {
        log_info(logger, "no url found in url queue");
        QCrawlerConfig* crawler_config =  QCrawlerConfig::getInstance();
        if (crawler_config->quit_on_no_url_found()) {
            exit(2);
        } else {
            QCrawlerSleep::sleep(1);
        }

        return;
    }

    log_debug(logger, "check freq control: " << crawl_url->host());
    while (!freq_control->canCrawl(crawl_url->host())) {
        log_debug(logger, "sleep 1 when crawl host: " << crawl_url->host());
        QCrawlerSleep::sleep(1);
    }

    QCrawlerUrl::UrlStatus url_status;
    bool get_ok = crawler_db->getUrlStatus(crawl_url->url(), &url_status);

    log_info(logger, "get url: " << crawl_url->url() << "status: " << url_status);

    bool valid = true;
    if (!get_ok) {
        valid = false;
    } else if (url_status == QCrawlerUrl::NOT_EXIST) {
        crawler_db->updateUrlStatus(crawl_url->url(), QCrawlerUrl::NOT_CRAWLED);
        valid = true;
    } else if (url_status > 0 && crawl_url->crawl_type() != QCrawlerUrl::UPDATE) { //
        valid = false;
    } else if (url_status < -3) {
        valid = false;
    } else {

    }

    log_debug(logger, "process status " << valid);
    emit processFinished(valid, rec);
}

#include "qcrawler_get_task.h"
#include "qcrawler_util.h"

#include "unistd.h"

void QCrawlerGetTask::process(bool r, QCrawlerRecord &rec) {
    if (!r) {
        return;
    }

    static int first_time = true;

    QCrawlerUrl* crawl_url = rec.mutable_crawl_url();
    if (first_time) {
        first_time = false;
        std::string url = "http://travel.sina.com.cn/";
        //std::string url = "http://travel.sina.com.cn/china/2008-08-07/174113097.shtml";
        std::string host = "travel.sina.com.cn";
        QCrawlerUrl::CrawlType crawl_type = QCrawlerUrl::HOST_RESTRICTED;
        int level = 0;

        crawl_url->set_url(url);
        crawl_url->set_crawl_level(level);
        crawl_url->set_host(host);
        crawl_url->set_crawl_type(crawl_type);
    } else {
        std::string serial_str;
        if (url_queue->shift(&serial_str)) {
           crawl_url->ParseFromString(serial_str);
        } else {
            log_info(logger, "no url found in url queue");
            return;
        }
    }

    log_debug(logger, "check freq control: " << crawl_url->host());
    while (!freq_control->canCrawl(crawl_url->host())) {
        log_debug(logger, "sleep 1 when crawl host: " << crawl_url->host());
        system("sleep 1");
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

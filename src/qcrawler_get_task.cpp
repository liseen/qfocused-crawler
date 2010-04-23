#include "qcrawler_get_task.h"
#include "qcrawler_util.h"
#include "qcrawler_sleep.h"
//#include "unistd.h"
#include <iostream>

int QCrawlerGetTask::process(QCrawlerRecord &rec) {
    static int first_time = true;

    if (first_time) {
        first_time = false;

        std::string url;
        while (std::cin >> url) {
            QUrl qurl(QString::fromUtf8(url.c_str()));
            if (qurl.isValid()) {
                QCrawlerUrl c_url;
                QString host = qurl.host();
                if (host.size() < 1) {
                    continue;
                }

                c_url.set_url(qurl.toString());
                c_url.set_crawl_level(0);
                c_url.set_crawl_type(QCrawlerUrl::HOST_RESTRICTED);
                c_url.set_status(QCrawlerUrl::NOT_EXIST);
                QByteArray bytes;
                c_url.serialize_to_bytes(bytes);
                url_queue->push(host, bytes);
            }
        }
    }

    QCrawlerUrl& crawl_url = rec.crawl_url();

    bool valid = false;
    QByteArray serial_bytes;
    if (url_queue->shift(&serial_bytes)) {
        valid = crawl_url.parse_from_bytes(serial_bytes);
    } else {
        if (QCrawlerConfig::getInstance()->quit_on_no_url_found()) {
            exit(2);
        } else {
            QCrawlerSleep::sleep(1);
        }

        valid = false;
    }

    // enabled freq control
    if (QCrawlerConfig::getInstance()->need_freq_control()) {
        while (!freq_control->canCrawl(crawl_url.host())) {
            QCrawlerSleep::sleep(1);
        }
    }

    emit processFinished(valid, rec);

    if (valid) {
        return 0;
    } else {
        return 1;
    }
}

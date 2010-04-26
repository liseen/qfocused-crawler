#include "qcrawler_get_task.h"
#include "qcrawler_util.h"
#include "qcrawler_sleep.h"
//#include "unistd.h"
#include <iostream>

int QCrawlerGetTask::process(QCrawlerRecord &rec) {
    QCrawlerUrl& crawl_url = rec.crawl_url();

    bool valid = false;
    QByteArray serial_bytes;
    if (url_queue->shift(&serial_bytes)) {
        valid = crawl_url.parse_from_bytes(serial_bytes);
        if (valid) {
            QUrl qurl(crawl_url.url());
            valid = qurl.isValid();
        } else {
            fprintf(stderr, "invalid url: %s\n", crawl_url.url().toUtf8().constData());
        }
    } else {
        if (QCrawlerConfig::getInstance()->quit_on_no_url_found()) {
            exit(2);
        } else {
            QCrawlerSleep::sleep(1);
        }

        valid = false;
    }

    // enabled freq control
    if (valid && QCrawlerConfig::getInstance()->need_freq_control()) {
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

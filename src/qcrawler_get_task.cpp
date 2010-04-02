#include "qcrawler_get_task.h"
#include "qcrawler_util.h"


void QCrawlerGetTask::process(bool r, QCrawlerRecord &rec) {
    if (!r) {
        return;
    }

    static int first_time = true;

    QCrawlerUrl* crawl_url = rec.mutable_crawl_url();
    if (first_time) {
        first_time = false;
        //std::string url = "http://travel.sina.com.cn/";
        std::string url = "http://travel.sina.com.cn/china/2008-08-07/174113097.shtml";
        std::string host = "travel.sina.com.cn";
        QCrawlerUrl::CrawlType crawl_type = QCrawlerUrl::UPDATE;
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
            qDebug() << "shift queue failed";
            return;
        }
    }


    qDebug() << "get url: " << QString::fromUtf8(crawl_url->url().c_str());
    QCrawlerUrl::UrlStatus url_status = crawler_db->getUrlStatus(crawl_url->url());

    bool valid = true;
    if (url_status == QCrawlerUrl::NOT_EXIST) {
        crawler_db->updateUrlStatus(crawl_url->url(), QCrawlerUrl::NOT_CRAWLED);
        valid = true;
    } else if (url_status > 0 && crawl_url->crawl_type() != QCrawlerUrl::UPDATE) { //
        valid = false;
    } else if (url_status < -3) {
        valid = false;
    } else {

    }

    emit processFinished(valid, rec);
}

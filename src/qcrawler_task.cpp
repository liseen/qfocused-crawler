#include "qcrawler_task.h"
#include "qcrawler_util.h"


void QCrawlerTask::getUrl() {
    QCrawlerRecord* rec = QCrawlerRecord::default_instance().New();

    std::string url = "http://travel.sina.com.cn/";
    std::string host = "travel.sina.com.cn";
    QCrawlerUrl::CrawlType crawl_type = QCrawlerUrl::UPDATE;

    int level = 0;

    QCrawlerUrl* crawl_url = rec->mutable_crawl_url();

    crawl_url->set_url(url);
    crawl_url->set_crawl_level(level);
    crawl_url->set_host(host);
    crawl_url->set_crawl_type(crawl_type);

    QCrawlerUrl::UrlStatus url_status = qcrawler_db->getUrlStatus(url);

    bool valid = true;
    if (url_status == QCrawlerUrl::NOT_EXIST) {
        valid = true;
    } else if (url_status > 0 && crawl_type != QCrawlerUrl::UPDATE) { //
        valid = false;
    } else if (url_status < -3) {
        valid = false;
    } else {

    }

    emit urlGetFinished(valid, *rec);

    debug_record(*rec);
    //TODO destory rec
}

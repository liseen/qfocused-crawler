#include "qcrawler_task.h"
#include "qcrawler_util.h"


void QCrawlerTask::getUrl() {
    QCrawlerRecord* rec = QCrawlerRecord::default_instance().New();

    std::string url = "http://travel.sina.com.cn/";
    int level = 0;

    QCrawlerUrl* crawl_url = rec->mutable_crawl_url();

    crawl_url->set_url(url);
    crawl_url->set_crawl_level(level);

    emit urlGetFinished(true, *rec);

    debug_record(*rec);
    //TODO destory rec
}

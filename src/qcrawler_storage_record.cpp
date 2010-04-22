#include "qcrawler_storage_record.h"


int QCrawlerStorageRecord::process(QCrawlerRecord &rec) {
    if (! crawler_db->updateUrlStatus(rec.crawl_url().url(), QCrawlerUrl::CRAWLED_OK) ) {
        return -1;
    }
    if (!crawler_db->storeRecord(rec)) {
        return -1;
    }

    return 0;
}



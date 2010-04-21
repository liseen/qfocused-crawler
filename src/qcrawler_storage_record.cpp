#include "qcrawler_storage_record.h"


int QCrawlerStorageRecord::process(QCrawlerRecord &rec) {
    bool r = crawler_db->storeRecord(rec);
    if (r) {
        return 0;
    } else {
        return -1;
    }
}



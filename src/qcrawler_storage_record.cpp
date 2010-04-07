#include "qcrawler_storage_record.h"


void QCrawlerStorageRecord::process(bool r, QCrawlerRecord &rec) {
    if (!r) {
        return;
    }

    bool store_ret = crawler_db->storeRecord(rec);

    log_debug(logger, "process status: " << store_ret);
    emit processFinished(store_ret, rec);
}



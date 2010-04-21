#include "qcrawler_freq_control.h"



bool QCrawlerFreqControl::canCrawl(const QString &host) {
    memcached_return rc;
    rc = memcached_add(memc, host.toUtf8().constData(), host.length(),
                            "1", 1,
                cycle_time, NULL);

    if (rc == MEMCACHED_SUCCESS) {
        return true;
    } else if (rc == MEMCACHED_NOTSTORED) {
        return false;
    } else {
        return false;
    }
}

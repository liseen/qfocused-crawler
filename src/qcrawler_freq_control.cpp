#include "qcrawler_freq_control.h"



bool QCrawlerFreqControl::canCrawl(const std::string &host) {
    memcached_return rc;
    rc = memcached_add(memc, host.c_str(), host.length(),
                            "1", 1,
                cycle_time, NULL);

    if (rc == MEMCACHED_SUCCESS) {
        log_debug(logger, "can crawl status ture, host: " << host);
        return true;
    } else if (rc == MEMCACHED_NOTSTORED) {
        log_debug(logger, "can crawl status false, host: " << host);
        return false;
    } else {
        log_fatal(logger, "memcached add error" <<  memcached_strerror(memc, rc));
        return false;
    }
}

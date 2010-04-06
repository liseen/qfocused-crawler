#ifndef QCRAWLER_FREQ_CONTROL_H
#define QCRAWLER_FREQ_CONTROL_H

#include "qcrawler_common.h"
#include "qcrawler_util.h"

#include "qcrawler_config.h"

#include <libmemcached/memcached.h>
#include <QObject>

class QCrawlerFreqControl : QObject
{
    Q_OBJECT

public:
    QCrawlerFreqControl() {
        logger = get_qcrawler_logger("freq_control");

        QCrawlerConfig *crawler_config = QCrawlerConfig::getInstance();

        cycle_time = crawler_config->freq_control_cycle_time();
        servers_str =  crawler_config->freq_control_memcached_servers();

        log_debug(logger, "freq control memcached servers: " << servers_str );

        memc = memcached_create(NULL);
        memcached_server_st *servers;
        servers= memcached_servers_parse((char*)servers_str.c_str());
        if (servers != NULL) {
            memcached_server_push(memc, servers);
            memcached_server_list_free(servers);
        } else {
            log_fatal(logger, "freq control memcached server config error or no servers found");
        }

        //log_debug(logger, "freq control memcached set binary protocal");
        //memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_BINARY_PROTOCOL, 1);

    }

    ~QCrawlerFreqControl() {
        memcached_free(memc);
    }

    bool canCrawl(const std::string &host);

private:
    QCrawlerLogger logger;
    memcached_st *memc;
    int cycle_time;
    std::string servers_str;
};

#endif

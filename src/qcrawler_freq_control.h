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
        QCrawlerConfig *crawler_config = QCrawlerConfig::getInstance();

        cycle_time = crawler_config->freq_control_cycle_time();
        servers_str =  crawler_config->freq_control_memcached_servers();

        memc = memcached_create(NULL);
        memcached_server_st *servers;
        servers= memcached_servers_parse(servers_str.toUtf8().data());
        if (servers != NULL) {
            memcached_server_push(memc, servers);
            memcached_server_list_free(servers);
        } else {
            fprintf(stderr, "freq control memcached server config error or no servers found\n");
        }

        //log_debug(logger, "freq control memcached set binary protocal");
        //memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_BINARY_PROTOCOL, 1);

    }

    ~QCrawlerFreqControl() {
        memcached_free(memc);
    }

    bool canCrawl(const QString &host);

private:
    memcached_st *memc;
    int cycle_time;
    QString servers_str;
};

#endif

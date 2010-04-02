#ifndef QCRAWLER_DB_H
#define QCRAWLER_DB_H

#include <QObject>
#include <QDebug>

#include <tcrdb.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "qcrawler_common.h"
#include "qcrawler_util.h"
#include "qcrawler_config.h"

class QCrawlerDB : public QObject
{
    Q_OBJECT

public:
    QCrawlerDB() {
        QCrawlerConfig *crawler_config = QCrawlerConfig::getInstance();

        url_hash_db_host = crawler_config->url_hash_db_host();
        url_hash_db_port = crawler_config->url_hash_db_port();
        record_db_type = crawler_config->record_db_type();
        record_db_host = crawler_config->record_db_host();
        record_db_port = crawler_config->record_db_port();

        //config
        record_db = tcrdbnew();
        if(!tcrdbopen(record_db, record_db_host.c_str(), record_db_port)){
            int ecode = tcrdbecode(record_db);
            fprintf(stderr, "open error: %s\n", tcrdberrmsg(ecode));
        }

        url_hash_db = tcrdbnew();
        if(!tcrdbopen(url_hash_db, url_hash_db_host.c_str(), url_hash_db_port)){
            int ecode = tcrdbecode(url_hash_db);
            fprintf(stderr, "open error: %s\n", tcrdberrmsg(ecode));
        }
    }

    ~QCrawlerDB() {
        /* close the connection */
        if(!tcrdbclose(record_db)){
            int ecode = tcrdbecode(record_db);
            fprintf(stderr, "close error: %s\n", tcrdberrmsg(ecode));
        }

        tcrdbdel(record_db);
    }

    bool storeRecord(const QCrawlerRecord &rec);
    QCrawlerUrl::UrlStatus getUrlStatus(std::string url);
    bool updateUrlStatus(std::string url, int);

private:
    TCRDB *record_db;
    std::string record_db_type;
    std::string record_db_host;
    int record_db_port;

    TCRDB *url_hash_db;
    std::string url_hash_db_host;
    int url_hash_db_port;
};

#endif

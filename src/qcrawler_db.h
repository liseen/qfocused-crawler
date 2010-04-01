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

#include "qcrawler_processor.h"

class QCrawlerDB : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerDB() {
        // TODO config
        record_db = tcrdbnew();
        if(!tcrdbopen(record_db, "localhost", 1978)){
            int ecode = tcrdbecode(record_db);
            fprintf(stderr, "open error: %s\n", tcrdberrmsg(ecode));
        }

        url_hash_db = tcrdbnew();
        if(!tcrdbopen(url_hash_db, "localhost", 1979)){
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

public slots:
    virtual void process(bool r, QCrawlerRecord &rec);

private:
    TCRDB *record_db;

    TCRDB *url_hash_db;
};

#endif

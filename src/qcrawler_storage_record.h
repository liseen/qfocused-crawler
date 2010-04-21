#ifndef QCRAWLER_STORAGE_RECORD_H
#define QCRAWLER_STORAGE_RECORD_H

#include <QObject>
#include <QDebug>

#include <tcrdb.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "qcrawler_common.h"
#include "qcrawler_util.h"

#include "qcrawler_db.h"
#include "qcrawler_processor.h"

class QCrawlerStorageRecord : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerStorageRecord(QCrawlerDB * db, QCrawlerUrlQueue *queue) :QCrawlerProcessor(db, queue) {
        //QCrawlerConfig *crawler_config = QCrawlerConfig::getInstance();
        // TODO config

    }



public slots:
    virtual int process(QCrawlerRecord &rec);

private:
};

#endif

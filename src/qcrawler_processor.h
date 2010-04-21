#ifndef QCRALER_PROCESSOR_H
#define QCRALER_PROCESSOR_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_db.h"
#include "qcrawler_url_queue.h"

class QCrawlerProcessor : public QObject
{
    Q_OBJECT

public:
    QCrawlerProcessor(QCrawlerDB *db, QCrawlerUrlQueue *queue) {
        crawler_db = db;
        url_queue = queue;
    }

public slots:
    virtual int process(QCrawlerRecord &rec);

signals:
    void processFinished(bool, QCrawlerRecord &rec);

protected:
    QCrawlerDB *crawler_db;
    QCrawlerUrlQueue* url_queue;
};

#endif

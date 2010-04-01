#ifndef QCRAWLER_FOCUS_FILTER_H
#define QCRAWLER_FOCUS_FILTER_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_util.h"

#include "qcrawler_db.h"
#include "qcrawler_processor.h"

class QCrawlerFocusFilter : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerFocusFilter(QCrawlerDB * qc_db) {
        qcrawler_db = qc_db;

        // TODO config
    }

    virtual ~QCrawlerFocusFilter() {
    }

public:
    virtual bool contentFilter(QCrawlerRecord &rec);
    virtual bool urlFilter(QCrawlerRecord &rec);

    bool insertFocusedUrls(const QCrawlerRecord &rec);

public slots:
    virtual void process(bool r, QCrawlerRecord &rec);

private:
    QCrawlerDB * qcrawler_db;
};


#endif

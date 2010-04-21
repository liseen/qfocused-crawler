#ifndef QCRAWLER_FOCUS_FILTER_H
#define QCRAWLER_FOCUS_FILTER_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_util.h"

#include "qcrawler_processor.h"


class QCrawlerFocusFilter : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerFocusFilter(QCrawlerDB * db, QCrawlerUrlQueue *queue) :QCrawlerProcessor(db, queue) {
    }

    virtual ~QCrawlerFocusFilter() {
    }

public:
    virtual bool contentFilter(QCrawlerRecord &rec);
    virtual bool urlFilter(QCrawlerRecord &rec);

    bool insertFocusedUrls(QCrawlerRecord &rec);

public slots:
    virtual int process(QCrawlerRecord &rec);

private:
};

#endif

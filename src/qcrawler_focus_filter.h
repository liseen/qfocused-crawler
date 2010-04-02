#ifndef QCRAWLER_FOCUS_FILTER_H
#define QCRAWLER_FOCUS_FILTER_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_util.h"

#include "qcrawler_processor.h"

#define MAX_CRAWL_LEVEL_DEFAULT 100

class QCrawlerFocusFilter : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerFocusFilter(QCrawlerDB * db, QCrawlerUrlQueue *queue) :QCrawlerProcessor(db, queue) {
        logger = get_qcrawler_logger("focus_filter");
        //QCrawlerConfig *crawler_config = QCrawlerConfig::getInstance();
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
    QCrawlerLogger logger;
};

#endif

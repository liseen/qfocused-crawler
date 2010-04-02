#ifndef QCRALER_KIT_PARSER_H
#define QCRALER_KIT_PARSER_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_util.h"
#include "qcrawler_processor.h"

#include "qcrawler_webpage.h"

class QCrawlerKitParser  : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerKitParser(QCrawlerDB *db, QCrawlerUrlQueue *queue): QCrawlerProcessor(db, queue) {
        //QCrawlerConfig *crawler_config = QCrawlerConfig::getInstance();
        // TODO config
        page = new QCrawlerPage();
    }

    ~QCrawlerKitParser() {
        delete page;
    }

public slots:
    virtual void process(bool r, QCrawlerRecord &rec);

private:
    QCrawlerPage* page;
};

#endif

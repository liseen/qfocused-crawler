#ifndef QCRALER_H
#define QCRALER_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_task.h"
#include "qcrawler_parser.h"
#include "qcrawler_processor.h"
/**
 * crawler
 */
class QCrawler : public QObject
{
    Q_OBJECT

public:
    QCrawler() {
        // TODO config
        task = new QCrawlerTask();
        parser = new QCrawlerParser();
        processor = new QCrawlerProcessor();

        QObject::connect(task, SIGNAL(urlGetFinished(bool, QCrawlerRecord &)),
                    parser, SLOT(parse(bool, QCrawlerRecord &)));
        QObject::connect(parser, SIGNAL(parseFinished(bool, QCrawlerRecord &)),
                    processor, SLOT(process(bool, QCrawlerRecord &)));
    }

    void start();

private:
    QCrawlerTask* task;
    QCrawlerParser* parser;
    QCrawlerProcessor* processor;
};

#endif

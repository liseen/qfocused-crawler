#include <QObject>
#include <QDebug>

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

        QObject::connect(task, SIGNAL(urlGetFinished(bool)),
                    parser, SLOT(parse(bool)));
        QObject::connect(parser, SIGNAL(parseFinished(bool)),
                    processor, SLOT(process(bool)));
    }

    void start();

private:
    QCrawlerTask* task;
    QCrawlerParser* parser;
    QCrawlerProcessor* processor;
};

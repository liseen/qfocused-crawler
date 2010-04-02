#ifndef QCRAWLER_URL_QUEUE_H
#define QCRAWLER_URL_QUEUE_H

#include <QObject>
#include <QDebug>
#include <QQueue>

#include "qcrawler_config.h"

class QCrawlerUrlQueue : public QObject {
    Q_OBJECT

public:
    QCrawlerUrlQueue() {
        //QCrawlerConfig *crawler_config = QCrawlerConfig::getInstance();
        // TODO config
    }

    void push(const std::string &content);

    bool shift(std::string *str);
private:
    QQueue<std::string> queue;
};

#endif

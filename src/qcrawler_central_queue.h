#ifndef QCRAWLER_CENTRAL_QUEUE_H
#define QCRAWLER_CENTRAL_QUEUE_H

#include "url_queue_client.h"

#include "qcrawler_config.h"
#include "qcrawler_url_queue.h"

class QCrawlerCentralQueue : public QCrawlerUrlQueue {
    Q_OBJECT

public:
    QCrawlerCentralQueue() {
        QCrawlerConfig *config = QCrawlerConfig::getInstance();
        std::string server = config->url_queue_server();
        client = new UrlQueueClient(server);
    }

    ~QCrawlerCentralQueue() {
        delete client;
    }

    virtual void push(const std::string &host, const std::string &content);

    virtual bool shift(std::string *str);
private:
    UrlQueueClient *client;
};

#endif


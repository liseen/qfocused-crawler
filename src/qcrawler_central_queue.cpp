#include "qcrawler_central_queue.h"



void QCrawlerCentralQueue::push(const std::string &host, const std::string &content) {
    client->push(host, content);
}

bool QCrawlerCentralQueue::shift(std::string *str) {
    return client->shift(str);
}


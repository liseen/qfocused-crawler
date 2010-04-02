#include "qcrawler_url_queue.h"

void QCrawlerUrlQueue::push(const std::string &content) {
    qDebug() << "enter queue ";
    queue.enqueue(content);
}

bool QCrawlerUrlQueue::shift(std::string *str) {
    qDebug() << "shift queue ";
    if (!queue.isEmpty()) {
        *str = queue.dequeue();
        return true;
    }

    return false;
}



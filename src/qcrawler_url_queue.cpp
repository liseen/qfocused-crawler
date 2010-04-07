#include "qcrawler_url_queue.h"

void QCrawlerUrlQueue::push(const std::string &host, const std::string &content) {
    if (host_map.contains(host)) {
        host_map[host].enqueue(content);
    } else {
        QQueue<std::string> q;
        q.enqueue(content);
        host_map.insert(host, q);
    }
}

bool QCrawlerUrlQueue::shift(std::string *str) {
    //if (!queue.isEmpty()) {
    //    *str = queue.dequeue();
    //    return true;
    //}

    if (host_map.size() < 1) {
        return false;
    }

    if (it == host_map.end()) {
        it = host_map.begin();
    }


    bool status = false;
    while (it != host_map.end()) {
        if (! (*it).isEmpty()) {
            *str = (*it).dequeue();
            status = true;
            ++it;
            break;
        }

        ++it;
    }

       return status;
}



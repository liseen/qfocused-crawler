#include "qcrawler_url_queue.h"

void QCrawlerUrlQueue::push(const std::string &host, const std::string &content) {
    //fprintf(stderr, "host map's add host: %s\n", host.c_str());
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

    //fprintf(stderr, "host map's size: %d\n", host_map.size());
    if (host_map.size() < 1) {
        return false;
    }

    if (it == host_map.end()) {
        it = host_map.begin();
    }


    bool status = false;
    while (it != host_map.end()) {
    	//fprintf(stderr, "shift host map: %s, queue size: %d\n", it.key().c_str(), it.value().size());
        if (! it.value().isEmpty()) {
            *str = it.value().dequeue();
            status = true;
            ++it;
            break;
        }

        ++it;
    }

    return status;
}



#include "qcrawler_focus_filter.h"

void QCrawlerFocusFilter::process(bool r, QCrawlerRecord &rec) {
    if (!r) {
        return;
    }

    std::string url = rec.crawl_url().url();

    QCrawlerUrl::UrlStatus url_status;

    if (contentFilter(rec)) {
        url_status = QCrawlerUrl::CRAWLED_OK;
        crawler_db->updateUrlStatus(url, url_status);
    } else {
        url_status = QCrawlerUrl::NOT_NEED_CRAWL;

        crawler_db->updateUrlStatus(url, url_status);
        // wo don't need check sub url here?
        emit processFinished(false, rec);
        return;
    }

    urlFilter(rec);

    insertFocusedUrls(rec);
}



bool QCrawlerFocusFilter::contentFilter(QCrawlerRecord &rec) {

    return true;
}


bool QCrawlerFocusFilter::urlFilter(QCrawlerRecord &rec) {
    // search url in hash database
    // move sub links to
    int size =rec.raw_sub_links_size();
    for (int i = 0; i < size; i++) {
        std::string url = rec.raw_sub_links(i).url();
        std::string host = rec.raw_sub_links(i).host();
        int crawl_level = rec.raw_sub_links(i).crawl_level();

        // TODO some url filter alogrithm
        QCrawlerUrl::UrlStatus url_status = crawler_db->getUrlStatus(url);


        if (host == "travel.sina.com.cn"
                && url_status == QCrawlerUrl::NOT_EXIST
                && crawl_level < MAX_CRAWL_LEVEL_DEFAULT) {
            QCrawlerUrl* focus_url = rec.add_focused_links();
            focus_url->CopyFrom(rec.raw_sub_links(i));

            crawler_db->updateUrlStatus(url, QCrawlerUrl::NOT_CRAWLED);
        }
    }
    return true;
}


bool QCrawlerFocusFilter::insertFocusedUrls(const QCrawlerRecord &rec) {
    // step 1: insert url to hash database
    //
    // enter url queue
    int size =rec.focused_links_size();
    for (int i = 0; i < size; i++) {
        std::string url = rec.focused_links(i).url();
        crawler_db->updateUrlStatus(url, QCrawlerUrl::NOT_CRAWLED);

        std::string serial_str;
        rec.focused_links(i).SerializeToString(&serial_str);

        url_queue->push(serial_str);
    }

    return true;
}



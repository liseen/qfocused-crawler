#include "qcrawler_focus_filter.h"

#include "qcrawler_focus_filter.h"

void QCrawlerFocusFilter::process(bool r, QCrawlerRecord &rec) {
    std::string url = rec.crawl_url().url();

    QCrawlerUrl::UrlStatus url_status;

    if (!r) {
        url_status = qcrawler_db->getUrlStatus(url);
        if (url_status <= 0) {
            qcrawler_db->updateUrlStatus(url, url_status - 1);
        }

        return;
    }


    if (contentFilter(rec)) {
        url_status = QCrawlerUrl::CRAWLED_OK;
        qcrawler_db->updateUrlStatus(url, url_status);
    } else {
        url_status = QCrawlerUrl::NOT_NEED_CRAWL;

        qcrawler_db->updateUrlStatus(url, url_status);
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

        // TODO some url filter alogrithm
        QCrawlerUrl::UrlStatus url_status = qcrawler_db->getUrlStatus(url);

        if (host == "travel.sina.com.cn" && url_status == QCrawlerUrl::NOT_EXIST) {
            QCrawlerUrl* focus_url = rec.add_focused_links();
            focus_url->CopyFrom(rec.raw_sub_links(i));

            qcrawler_db->updateUrlStatus(url, QCrawlerUrl::NOT_CRAWLED);
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
        qcrawler_db->updateUrlStatus(url, QCrawlerUrl::NOT_CRAWLED);
    }

    return true;
}



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
    }

    if (urlFilter(rec)) {

    }

    insertFocusedUrls(rec);

    emit processFinished(true, rec);
}



bool QCrawlerFocusFilter::contentFilter(QCrawlerRecord &rec) {

    return true;
}


bool QCrawlerFocusFilter::urlFilter(QCrawlerRecord &rec) {
    QCrawlerUrl::CrawlType crawl_type = rec.crawl_url().crawl_type();
    std::string host = rec.crawl_url().host();
    int size =rec.raw_sub_links_size();
    for (int i = 0; i < size; i++) {
        std::string sub_url = rec.raw_sub_links(i).url();
        std::string sub_host = rec.raw_sub_links(i).host();
        int sub_crawl_level = rec.raw_sub_links(i).crawl_level();

        // TODO some url filter alogrithm
        QCrawlerUrl::UrlStatus url_status;
        if (crawler_db->getUrlStatus(sub_url, &url_status)) {
            if (sub_crawl_level > MAX_CRAWL_LEVEL_DEFAULT) {
                continue;
            }

            if (url_status != QCrawlerUrl::NOT_EXIST) { // already have
                continue;
            }

            if (crawl_type == QCrawlerUrl::HOST_RESTRICTED) {
                if (sub_host == host) {
                    QCrawlerUrl* focus_url = rec.add_focused_links();
                    focus_url->CopyFrom(rec.raw_sub_links(i));

                    crawler_db->updateUrlStatus(sub_url, QCrawlerUrl::NOT_CRAWLED);
                    log_debug(logger, "added focus url:" << sub_url);
                }
            } else if (crawl_type == QCrawlerUrl::UPDATE) { // update , we don't extract sub links
                break;
            } else {

            }
        } else {
            return false;
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

        url_queue->push(rec.focused_links(i).host(), serial_str);
    }

    return true;
}



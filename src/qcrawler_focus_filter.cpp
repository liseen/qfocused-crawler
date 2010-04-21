#include "qcrawler_focus_filter.h"

int QCrawlerFocusFilter::process(QCrawlerRecord &rec) {

    QString url = rec.crawl_url().url();
    QCrawlerUrl::Status url_status;

    if (! contentFilter(rec)) {
        url_status = QCrawlerUrl::NOT_NEED_CRAWL;

        crawler_db->updateUrlStatus(url, url_status);
        emit processFinished(false, rec);
        return 1;
    }

    urlFilter(rec);

    insertFocusedUrls(rec);

    emit processFinished(true, rec);

    return 0;
}



bool QCrawlerFocusFilter::contentFilter(QCrawlerRecord &) {

    return true;
}


bool QCrawlerFocusFilter::urlFilter(QCrawlerRecord &rec) {
    QCrawlerUrl::CrawlType crawl_type = rec.crawl_url().crawl_type();
    QString host = rec.crawl_url().host();
    int size =rec.raw_sub_links().size();
    for (int i = 0; i < size; i++) {
        QString sub_url = rec.raw_sub_links(i).url();
        QString sub_host = rec.raw_sub_links(i).host();
        int sub_crawl_level = rec.raw_sub_links(i).crawl_level();

        // TODO some url filter alogrithm
        QCrawlerUrl::Status url_status;
        if (crawler_db->getUrlStatus(sub_url, &url_status)) {
            if (sub_crawl_level > MAX_CRAWL_LEVEL) {
                continue;
            }

            if (crawl_type == QCrawlerUrl::HOST_RESTRICTED) {
                if (url_status != QCrawlerUrl::NOT_EXIST) { // already have
                    continue;
                }

                // end with host
                if (sub_host.endsWith(host)) {
                    qDebug() << "new focus url: " << sub_url;
                    rec.focused_links().append(rec.raw_sub_links(i));
                    rec.focused_links().last().set_crawl_type(crawl_type);
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


bool QCrawlerFocusFilter::insertFocusedUrls(QCrawlerRecord &rec) {
    int size =rec.focused_links().size();
    for (int i = 0; i < size; i++) {
        QString url = rec.focused_links(i).url();
        crawler_db->updateUrlStatus(url, QCrawlerUrl::NOT_CRAWLED);
        QByteArray bytes;
        if (rec.focused_links(i).serialize_to_bytes(bytes)) {
            url_queue->push(rec.focused_links(i).host(), bytes);
        } else {
            //TODO log
        }
    }

    return true;
}



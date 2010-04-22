#include "qcrawler_db.h"


bool QCrawlerDB::storeRecord(const QCrawlerRecord &rec) {
    QString url = rec.crawl_url().url();
    QString url_md5 = md5_hash(url);
    QString parent_url_md5 = rec.crawl_url().parent_url_md5();

    int crawl_level = rec.crawl_url().crawl_level();
    QString anchor_text = rec.crawl_url().anchor_text();
    QString raw_html = rec.raw_html();
    QString raw_title = rec.raw_title();
    QString raw_content = rec.raw_content();
    QString raw_content_md5 = md5_hash(raw_content);

    int download_time = rec.download_time();
    int last_modified = rec.last_modified();
    int loading_time =  rec.loading_time();

    int key_size = url.size();

    TCMAP *cols = tcmapnew();
    tcmapput2(cols, "url", url.toUtf8().constData());
    tcmapput2(cols, "url_md5", url_md5.toUtf8().constData());
    tcmapput2(cols, "parent_url_md5", parent_url_md5.toUtf8().constData());
    tcmapput2(cols, "crawl_level", QByteArray::number(crawl_level).constData());
    tcmapput2(cols, "anchor_text", anchor_text.toUtf8().constData());
    tcmapput2(cols, "raw_html", raw_html.toUtf8().constData());
    tcmapput2(cols, "raw_title", raw_title.toUtf8().constData());
    tcmapput2(cols, "raw_content", raw_content.toUtf8().constData());
    tcmapput2(cols, "raw_content_md5", raw_content_md5.toUtf8().constData());

    tcmapput2(cols, "download_time", QByteArray::number(download_time).constData());
    tcmapput2(cols, "last_modified", QByteArray::number(last_modified).constData());
    tcmapput2(cols, "loading_time", QByteArray::number(loading_time).constData());

    bool status = true;
    if(!tcrdbtblput(record_db, url.toUtf8().constData(), key_size, cols)){
        int ecode = tcrdbecode(record_db);
        fprintf(stderr, "store record put error: %s\n",  tcrdberrmsg(ecode));
        status = false;
    }
    tcmapdel(cols);

    return status;
}

bool QCrawlerDB::getUrlStatus(QString url, QCrawlerUrl::Status *url_status) {
    bool ret = false;

    int status = 0;

    char *value;
    value = tcrdbget2(url_hash_db, url.toUtf8().constData());
    if(value){
        status = atoi(value);
        if (status < -5) {
            status = -5;
        }

        *url_status = (QCrawlerUrl::Status)status;
        ret = true;

        free(value);
    } else {
        int ecode = tcrdbecode(url_hash_db);
        if (ecode == 7) {
            *url_status = QCrawlerUrl::NOT_EXIST;
            ret = true;
        } else {
            fprintf(stderr, "get url status error: %s", tcrdberrmsg(ecode));
            ret = false;
        }
    }

    return ret;
}

bool QCrawlerDB::updateUrlStatus(const QString &url, int status) {
    char status_str[40];
    sprintf(status_str, "%d", status);

    if(!tcrdbput2(url_hash_db, url.toUtf8().constData(), status_str)) {
        int ecode = tcrdbecode(url_hash_db);
        fprintf(stderr, "update url status put error: %s",  tcrdberrmsg(ecode));
        return false;
    }

    return true;
}




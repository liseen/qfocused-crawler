#include "qcrawler_db.h"


bool QCrawlerDB::storeRecord(const QCrawlerRecord &rec) {
    std::string url = rec.crawl_url().url();
    int crawl_level = rec.crawl_url().crawl_level();
    std::string anchor_text = rec.crawl_url().anchor_text();
    std::string raw_html = rec.raw_html();
    std::string raw_title = rec.raw_title();
    std::string raw_content = rec.raw_content();
    int download_time = rec.download_time();
    int last_modified = rec.last_modified();
    int loading_time =  rec.loading_time();

    int key_size = url.size();

    TCMAP *cols = tcmapnew();
    tcmapput2(cols, "url", url.c_str());

    char crawl_level_str[40]; //enough for 64bit?
    sprintf(crawl_level_str, "%d", crawl_level);
    tcmapput2(cols, "crawl_level", crawl_level_str);
    tcmapput2(cols, "anchor_text", anchor_text.c_str());
    tcmapput2(cols, "raw_html", raw_html.c_str());
    tcmapput2(cols, "raw_title", raw_title.c_str());
    tcmapput2(cols, "raw_content", raw_content.c_str());

    char d_time[40]; //enough for 64bit?
    sprintf(d_time, "%d", download_time);

    char last_time[40]; //enough for 64bit?
    sprintf(last_time, "%d", last_modified);
    char lo_time[40]; //enough for 64bit?
    sprintf(lo_time, "%d", loading_time);
    tcmapput2(cols, "download_time", d_time);
    tcmapput2(cols, "last_modified", last_time);
    tcmapput2(cols, "loading_time", lo_time);

    bool status = true;
    if(!tcrdbtblput(record_db, url.c_str(), key_size, cols)){
        int ecode = tcrdbecode(record_db);
        log_error(logger, "store record put error: " << tcrdberrmsg(ecode));
        status = false;
    }
    tcmapdel(cols);

    return status;
}

bool QCrawlerDB::getUrlStatus(std::string url, QCrawlerUrl::UrlStatus *url_status) {
    bool ret = false;

    int status = 0;

    char *value;
    value = tcrdbget2(url_hash_db, url.c_str());
    if(value){
        status = atoi(value);
        if (QCrawlerUrl_UrlStatus_IsValid(status)) {
            *url_status = (QCrawlerUrl::UrlStatus)status;
            ret = true;
        }

        free(value);
    } else {
        int ecode = tcrdbecode(url_hash_db);
        if (ecode == 7) {
            *url_status = QCrawlerUrl::NOT_EXIST;
            ret = true;
        } else {
            log_error(logger, "get error: " << tcrdberrmsg(ecode));
            ret = false;
        }
    }

    return ret;
}

bool QCrawlerDB::updateUrlStatus(const std::string &url, int status) {
    log_debug(logger, "update status: " << status << " url: " <<  url);

    char status_str[40];
    sprintf(status_str, "%d", status);

    if(!tcrdbput2(url_hash_db, url.c_str(), status_str)) {
        int ecode = tcrdbecode(url_hash_db);
        log_debug(logger, "update url status put error: " << tcrdberrmsg(ecode));
        return false;
    }

    return true;
}




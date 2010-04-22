#include "qcrawler_kit_parser.h"
#include "qcrawler_util.h"

#include <QList>
#include <QWebElement>
#include <QTime>

int QCrawlerKitParser::process(QCrawlerRecord &rec) {
    QString url = rec.crawl_url().url();
    int crawl_level = rec.crawl_url().crawl_level();

    QTime begin_time;
    begin_time.start();
    bool loadRet =  page->crawlerLoad(QUrl(url));

    if (loadRet) {
        QWebFrame* frame = page->mainFrame();
        QString raw_title = frame->title();
        QString raw_html = frame->toHtml();
        QString raw_content = frame->toPlainText();

        rec.set_raw_title(frame->title());
        rec.set_raw_html(frame->toHtml());
        rec.set_raw_content(frame->toPlainText());
        rec.set_download_time(get_current_time());
        rec.set_loading_time(begin_time.elapsed());

        // TODO get all links from
        // a => href area =>href base del=>cite
        // frame src longdesc
        // form => action
        // iframe => src
        // ilayer =>
        // background ...
        QWebElementCollection allLinks = frame->findAllElements("a,frame,iframe,area,map");
        // local unique first
        QHash<QString, int> dedupHash;
        foreach (QWebElement link, allLinks) {
            QString l = link.attribute("href");
            if (l.isEmpty()) {
                l = link.attribute("src");
            }

            QUrl qurl(l);
            if (qurl.isRelative() && qurl.hasFragment()) {
                l = qurl.toString(QUrl::StripTrailingSlash | QUrl::RemoveFragment);
                qurl.clear();
                qurl = QUrl(l);
            }

            if (qurl.isRelative()) {
                qurl = frame->baseUrl().resolved(l);
                l = qurl.toString(QUrl::StripTrailingSlash);
            }

            if (dedupHash.contains(l)) {
                continue;
            } else {
                dedupHash.insert(l, 0);
            }

            QStringList extens = QCrawlerConfig::getInstance()->focus_filter_bin_extensions();
            bool isBin = false;
            foreach (QString ext, extens) {
                if (l.endsWith("." + ext)) {
                    isBin = true;
                    break;
                }
            }

            if (isBin) { //we don't want crawl binnary file
                continue;
            }

            if (qurl.isValid() && qurl.scheme().startsWith("http")) {
                QCrawlerUrl* sub_url = rec.add_raw_sub_links();
                sub_url->set_url(qurl);
                sub_url->set_anchor_text(link.toPlainText());
                sub_url->set_url_md5(md5_hash(l));
                sub_url->set_parent_url_md5(md5_hash(url));
                sub_url->set_crawl_level(crawl_level + 1);
            }
        }
    } else {
        QCrawlerUrl::Status url_status = rec.crawl_url().status();
        if (url_status <= 0) {
            crawler_db->updateUrlStatus(url, url_status - 1);
        } else {
            crawler_db->updateUrlStatus(url, -1);
        }
    }

    emit processFinished(loadRet, rec);

    return 0;
}


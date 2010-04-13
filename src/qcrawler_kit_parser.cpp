#include "qcrawler_kit_parser.h"

#include <QList>
#include <QWebElement>

void QCrawlerKitParser::process(bool r, QCrawlerRecord &rec) {
    if (!r) {
        return;
    }

    std::string url = rec.crawl_url().url();
    int crawl_level = rec.crawl_url().crawl_level();


    bool loadRet =  page->crawlerLoad(QUrl(QString::fromUtf8(url.c_str())));
    log_debug(logger, "load status: " << loadRet);

    if (loadRet) {
        QWebFrame* frame = page->mainFrame();
        QString raw_title = frame->title();
        QString raw_html = frame->toHtml();
        QString raw_content = frame->toPlainText();

        rec.set_raw_title(frame->title().toUtf8().constData());
        rec.set_raw_html(frame->toHtml().toUtf8().constData());
        rec.set_raw_content(frame->toPlainText().toUtf8().constData());

        //QWebElement document = frame->documentElement();
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

            if (dedupHash.contains(l)) {
                continue;
            } else {
                dedupHash.insert(l, 0);
            }

            QUrl qurl(l);
            if (qurl.isRelative()) {
                qurl = frame->baseUrl().resolved(l);
            }

            if (!l.startsWith("#") && qurl.scheme().startsWith("http") && qurl.isValid()) {
                QCrawlerUrl* sub_url = rec.add_raw_sub_links();
                sub_url->set_url(qurl.toString().toUtf8().constData());
                sub_url->set_anchor_text(link.toPlainText().toUtf8().constData());
                sub_url->set_host(qurl.host().toUtf8().constData());
                sub_url->set_crawl_level(crawl_level + 1);
            }
        }
    } else {
        QCrawlerUrl::UrlStatus url_status;
        if (crawler_db->getUrlStatus(url, &url_status)) {
            if (url_status <= 0) {
                crawler_db->updateUrlStatus(url, url_status - 1);
            } else {
                crawler_db->updateUrlStatus(url, -1);
            }
        } else {
            loadRet = false;
        }
    }

    log_debug(logger, "process status: " << loadRet);
    emit processFinished(loadRet, rec);
}


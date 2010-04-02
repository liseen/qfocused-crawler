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
    if (loadRet) {
        QWebFrame* frame = page->mainFrame();
        QString raw_title = frame->title();
        QString raw_html = frame->toHtml();
        QString raw_content = frame->toPlainText();

        qDebug() << frame->title();
        fprintf(stderr, "title test: %s\n", frame->title().toUtf8().constData());
        rec.set_raw_title(frame->title().toUtf8().constData());
        rec.set_raw_html(frame->toHtml().toUtf8().constData());
        rec.set_raw_content(frame->toPlainText().toUtf8().constData());
        QWebElement document = frame->documentElement();
        // TODO get all links from
        // a => href area =>href base del=>cite
        // frame src longdesc
        // form => action
        // iframe => src
        // ilayer =>
        // background ...
        QWebElementCollection allLinks = document.findAll("a,frame,iframe,area,map");
        foreach (QWebElement link, allLinks) {
            QString l = link.attribute("href");
            if (l.length() > 1) {
                QCrawlerUrl* sub_url = rec.add_raw_sub_links();
                sub_url->set_url(l.toUtf8().constData());
                sub_url->set_crawl_level(crawl_level + 1);
            }

            l = link.attribute("href");
            QUrl qurl(l);
            if (qurl.isValid()) {
                QCrawlerUrl* sub_url = rec.add_raw_sub_links();
                sub_url->set_url(qurl.toString().toUtf8().constData());
                sub_url->set_host(qurl.host().toUtf8().constData());
                sub_url->set_crawl_level(crawl_level + 1);
            }

        }
    } else {
        QCrawlerUrl::UrlStatus url_status = crawler_db->getUrlStatus(url);
        if (url_status <= 0) {
            crawler_db->updateUrlStatus(url, url_status - 1);
        } else {
            crawler_db->updateUrlStatus(url, -1);
        }
    }

    //qDebug() << "parser\n";
    emit processFinished(loadRet, rec);
}

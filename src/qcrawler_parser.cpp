#include "qcrawler_parser.h"

#include <QList>
#include <QWebElement>

void QCrawlerParser::parse(bool r, QCrawlerRecord &rec) {
    std::string url = rec.crawl_url().url();

    if (!r) {
        return;
    }

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
        // TODO get links from a => href area =>href base del=>cite
        // frame src longdesc
        // form action
        // iframe src
        // ilayer =>
        // background ...
        QWebElementCollection allLinks = document.findAll("a");
        foreach (QWebElement link, allLinks) {
           qDebug() << link.attribute("href");
        }
    }
    qDebug() << "parser\n";
    emit parseFinished(loadRet, rec);
}


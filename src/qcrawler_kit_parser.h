#ifndef QCRALER_KIT_PARSER_H
#define QCRALER_KIT_PARSER_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_util.h"
#include "qcrawler_processor.h"

#include "qcrawler_webpage.h"
#include <qwebsettings.h>

class QCrawlerKitParser  : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerKitParser(QCrawlerDB *db, QCrawlerUrlQueue *queue): QCrawlerProcessor(db, queue) {
        logger = get_qcrawler_logger("kit_parser");
        QCrawlerConfig *config = QCrawlerConfig::getInstance();
        // TODO config
        page = new QCrawlerPage();

        page->settings()->setAttribute(QWebSettings::JavascriptEnabled, config->enable_js());
        page->settings()->setAttribute(QWebSettings::AutoLoadImages, config->auto_load_image());
        page->settings()->setAttribute(QWebSettings::JavaEnabled, false);
        page->settings()->setAttribute(QWebSettings::PluginsEnabled, false);
    }

    ~QCrawlerKitParser() {
        delete page;
    }

public slots:
    virtual void process(bool r, QCrawlerRecord &rec);

private:
    QCrawlerLogger logger;
    QCrawlerPage* page;
};

#endif

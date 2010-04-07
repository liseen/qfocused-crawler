#include <QApplication>
#include <QUrl>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    std::string default_conf_file = "etc/qcrawler.conf.default";
    std::string default_log_file = "etc/qcrawler_log.conf.default";
    GLOBAL_INIT_LOGGER(default_log_file);

    QCrawler* crawler = new QCrawler(default_conf_file);

    crawler->start();

    return app.exec();
}

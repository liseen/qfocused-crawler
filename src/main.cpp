#include <QApplication>
#include <QUrl>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler.h"

static void print_usage(FILE* out, int exit_code)
{
    fprintf(out, "Usage qcrawler <options>\n");
    fprintf(out,
            "  --help        Print this help\n"
            "  --conf=<path> Config file path\n"
            "  --verbose     Verbose\n"
           );

    exit(exit_code);
}


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QString conf_file = "etc/qcrawler.conf.default";

    const QStringList args = app.arguments();
    for (int i = 1; i < args.count(); i++) {
        QString arg = args.at(i);
        if (arg.indexOf("--help") == 0) {
            print_usage(stdout, 0);
        } else if (arg.indexOf("--verbose") == 0) {
        } else if (arg.indexOf("--conf=") == 0) {
            conf_file = arg.split("=").at(1);
        } else {
            print_usage(stderr, 1);
        }
    }

    QCrawlerConfig* config =  QCrawlerConfig::getInstance();
    bool init_ret = config->init(conf_file);
    if (!init_ret) {
        fprintf(stderr, "init configuration failed\n");
        exit(1);
    }

    QCrawler* crawler = new QCrawler();
    crawler->start();

    return app.exec();
}

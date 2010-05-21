#include <QApplication>
#include <QStringList>
#include <QUrl>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler.h"
#include <iostream>

static void print_usage(FILE* out, int exit_code)
{
    fprintf(out, "Usage qcrawler <crawl|add|extract> <options>\n");
    fprintf(out,
            "  --help        Print this help\n"
            "  --conf=<path> Config file path\n"
            "  --verbose     Verbose\n"
           );

    exit(exit_code);
}


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QString conf_file = "etc/qcrawler.conf";

    const QStringList args = app.arguments();

    QString cmd;
    for (int i = 1; i < args.count(); i++) {
        QString arg = args.at(i);
        if (i == 1) {
            cmd = arg;
        } else if (arg.indexOf("--help") == 0) {
            print_usage(stdout, 0);
        } else if (arg.indexOf("--verbose") == 0) {
        } else if (arg.indexOf("--conf=") == 0) {
            conf_file = arg.split("=").at(1);
        } else {
            print_usage(stderr, 1);
        }
    }
    if (cmd.isEmpty()) {
        fprintf(stderr, "No command specified\n");
        print_usage(stderr, 1);
    }

    QCrawlerConfig* config =  QCrawlerConfig::getInstance();
    bool init_ret = config->init(conf_file);
    if (!init_ret) {
        fprintf(stderr, "init configuration failed\n");
        exit(1);
    }

    QCrawlerUrlQueue *url_queue;
    if (QCrawlerConfig::getInstance()->enable_central_queue()) {
        url_queue = new QCrawlerCentralQueue();
    } else {
        url_queue = new QCrawlerUrlQueue();
    }

    if (cmd == "crawl") {
        QCrawler* crawler = new QCrawler(url_queue);
        crawler->start();
    } else if (cmd == "add") {
        QTextStream stream(stdin);
        QString line;
        do {
           line = stream.readLine();
           if (line.isEmpty()) {
               continue;
           }

           QStringList list = line.split("\t");
           if (list.size() < 1) {
               continue;
           }

           QUrl qurl(list.at(0), QUrl::StrictMode);
           if (qurl.isValid()) {
                QCrawlerUrl c_url;
                QString host = qurl.host();
                c_url.set_url(qurl.toString());
                c_url.set_crawl_level(0);
                QString type =  "host_restricted";
                if (list.size() > 1) {
                    type = list.at(1);
                }

                if (type == "host_restricted") {
                    c_url.set_crawl_type(QCrawlerUrl::HOST_RESTRICTED);
                } else if (type == "update") {
                    c_url.set_crawl_type(QCrawlerUrl::UPDATE);
                }

                QByteArray bytes;
                c_url.serialize_to_bytes(bytes);
                url_queue->push(host, bytes);
            } else {
                fprintf(stdout, "Invalid url: %s", line.toUtf8().constData());
            }
        } while (!line.isNull());
    } else if (cmd == "extract") {
        QTextStream stream(stdin);
        QTextStream out(stdout);

        QCrawlerSimpleExtractor *extractor = new QCrawlerSimpleExtractor(NULL, NULL);

        QString line;
        do {
            line = stream.readLine();
            if (line.isEmpty()) {
                continue;
            }
            QStringList list = line.split("\t");
            if (list.size() < 3) {
                continue;
            }
            QString url = list.at(0);
            QString title = extractor->extractTitle(list.at(1));
            QString raw_content = list.at(2);
            QString content = extractor->extractMainContent(raw_content.replace("\x01", "\n"));
            if (content.size() < 100) {
                //continue;
            }
            content.replace("\n", " ");

            out<< url << "\t" << title << "\t" << content << "\n";
        } while (!line.isNull());
    } else {
        fprintf(stderr, "No command %s found\n", cmd.toUtf8().constData());
        print_usage(stderr, 1);
    }

    return 0;
}

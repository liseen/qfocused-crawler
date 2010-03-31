#include <QApplication>
#include <QUrl>
#include <QDebug>
#include <QWebView>
#include <QWebPage>
#include <QWebFrame>

#include <iostream>
using namespace std;

// Get url from queue
// Get html, raw_title, raw_content, raw_links // parser 
// processor focused filter  //access db
// url filter to queue /access url hash db url filter

// parser input
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    //QWebView* view = new QWebView();
    //view->load(QUrl("http://www.google.com"));
    //view->show();

    QWebPage* page = new QWebPage();
    page->setViewportSize(QSize(1024, 728));
    page->settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
    QWebFrame* frame = page->mainFrame();
    frame->load(QUrl("http://www.google.com"));

    string str;
    cin>>str;
    qDebug() << frame->toHtml() << endl;
    qDebug() << frame->toHtml() << endl;

    return app.exec();
}

#include "qcrawler_webpage.h"
#include "qcrawler_eventloop.h"

#include <QSignalSpy>

QString
QCrawlerPage::chooseFile(QWebFrame* /*frame*/, const QString& /*suggestedFile*/) {
  return QString::null;
}

bool
QCrawlerPage::javaScriptConfirm(QWebFrame* /*frame*/, const QString& /*msg*/) {
  return true;
}

bool
QCrawlerPage::javaScriptPrompt(QWebFrame* /*frame*/,
                           const QString& /*msg*/,
                           const QString& /*defaultValue*/,
                           QString* /*result*/) {
  return true;
}

void
QCrawlerPage::javaScriptConsoleMessage(const QString& /*message*/,
                                   int /*lineNumber*/,
                                   const QString& /*sourceID*/) {
  // noop
}

void
QCrawlerPage::javaScriptAlert(QWebFrame* /*frame*/, const QString& /*msg*/) {
  // noop
}



QString
QCrawlerPage::userAgentForUrl(const QUrl& url) const {

  if (!mUserAgent.isNull())
    return mUserAgent;

  return QWebPage::userAgentForUrl(url);
}

bool
QCrawlerPage::crawlerLoad(const QUrl &url) {
    int mTimeout = 15 * 1000;
    //int mTimeout = -1;
    if (url.isValid()) {
        QCrawlerEventLoop loop;
        QObject::connect(this, SIGNAL(loadFinished(bool)), &loop,
                SLOT(quitWithRes(bool)));

        this->mainFrame()->load(url);

        if (!loop.checkFinished()) {
            QTimer timer;
            QSignalSpy timeoutSpy(&timer, SIGNAL(timeout()));
            if (mTimeout > 0) {
                QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
                timer.setSingleShot(true);
                timer.start(mTimeout);
            }
            loop.exec();

            if (!timeoutSpy.isEmpty()) {
                fprintf(stderr, "Page loading timeout (exceeded %d ms): %s\n",
                    mTimeout, url.toString().toUtf8().data());
                this->blockSignals(true);
                this->triggerAction(QWebPage::Stop);
                this->blockSignals(false);
                return false;
            } else if (!loop.getRes()) {
                fprintf(stderr, "Failed to load page: %s\n", url.toString().toUtf8().data());
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

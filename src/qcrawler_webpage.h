#ifndef QCRALER_WEBPAGE_H
#define QCRALER_WEBPAGE_H

#include <QtWebKit>

#include <QWebPage>

class QCrawlerPage : public QWebPage {
    Q_OBJECT

public:
    void setUserAgent(const QString& userAgent) {
        mUserAgent = userAgent;
    }

    bool crawlerLoad(const QUrl &qurl);

protected:
    QString chooseFile(QWebFrame *frame, const QString& suggestedFile);
    void javaScriptConsoleMessage(const QString& message, int lineNumber, const QString& sourceID);
    bool javaScriptPrompt(QWebFrame* frame, const QString& msg, const QString& defaultValue, QString* result);
    void javaScriptAlert(QWebFrame* frame, const QString& msg);
    bool javaScriptConfirm(QWebFrame* frame, const QString& msg);
    QString userAgentForUrl(const QUrl& url) const;
    QString mUserAgent;
};

#endif


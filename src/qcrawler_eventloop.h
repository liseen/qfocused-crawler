#ifndef QCRAWLER_EVENTLOOP_H
#define QCRAWLER_EVENTLOOP_H

#include <QDebug>
#include <QEventLoop>

class QCrawlerEventLoop: public QEventLoop {
    Q_OBJECT

public:
    QCrawlerEventLoop():isFinished(false) {}

public Q_SLOTS:
    void quitWithRes(bool res) {
        m_res = res;
        isFinished = true;
        quit();
    }

    bool getRes() {
        return m_res;
    }

    bool checkFinished() {
        return isFinished;
    }

private:
    bool m_res;
    bool isFinished;
};

#endif


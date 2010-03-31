#include <QObject>
#include <QDebug>

class QCrawlerParser : public QObject
{
    Q_OBJECT

public:
    QCrawlerParser() {
        // TODO config
    }

public slots:
    void parse(bool r);

signals:
    void parseFinished(bool);

};

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
    void parser();

signals:
    void parserFinished(bool);

};

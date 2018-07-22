#ifndef HEADTESTER_H
#define HEADTESTER_H

class HeadTester :public QObject
{
    Q_OBJECT

public:
    explicit HeadTester(const QString &url, QObject *parent = nullptr);
    Q_DISABLE_COPY(HeadTester);
    void     Start();

signals:
    void     SigFinished(bool ok, int elapsed);

private slots:
    void     OnFinished();

private:
    QNetworkRequest        mRequest;
    QNetworkAccessManager  mNam;
    QNetworkReply         *mpReply;
    QTime                  mTimer;
};

#endif
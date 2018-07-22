#ifndef HTTPDOWNLODER_H
#define HTTPDOWNLODER_H

class HttpDownloader :public QObject
{
    Q_OBJECT

public:
    explicit HttpDownloader(const QString &url, QObject *parent = nullptr);
    Q_DISABLE_COPY(HttpDownloader);
    void     Start();
    void     Cancel();

signals:
    void     SigProgressChanged(int p);
    void     SigSpeedChanged(qint64 speed);
    void     SigFinished(bool ok);

private slots:
    void     OnProgressChanged(qint64 bytesDownloaded, qint64 bytesTotal);
    void     OnReadyRead();
    void     OnFinished();
    void     OnSpeedTimer();

private:
    QNetworkRequest        mRequest;
    QNetworkAccessManager  mNam;
    QNetworkReply         *mpReply;
    QTime                  mTimer;
    qint64                 mnBytesDownloaded;
    qint64                 mnBytesTotal;
    qint64                 mnLastSpeed;
    QTimer                 mSpeedTimer;
};

#endif
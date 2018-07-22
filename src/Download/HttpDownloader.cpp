#include "HttpDownloader.h"

HttpDownloader::HttpDownloader(const QString &url, QObject *parent)
    : QObject(parent)
    , mpReply(nullptr)
    , mnBytesDownloaded(0)
    , mnBytesTotal(0)
    , mnLastSpeed(0)
{
    mRequest.setUrl(QUrl(url));
    QSslConfiguration conf = mRequest.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    mRequest.setSslConfiguration(conf);
    connect(&mSpeedTimer, &QTimer::timeout, this, &HttpDownloader::OnSpeedTimer);
}

void HttpDownloader::Start()
{
    if (mpReply)
    {
        return;
    }
    mTimer.restart();
    mnBytesDownloaded = 0;
    mnBytesTotal = 0;
    mnLastSpeed = 0;
    mpReply = mNam.get(mRequest);
    connect(mpReply, &QNetworkReply::downloadProgress, this, &HttpDownloader::OnProgressChanged);
    connect(mpReply, &QNetworkReply::readyRead, this, &HttpDownloader::OnReadyRead);
    connect(mpReply, &QNetworkReply::finished, this, &HttpDownloader::OnFinished);
    mSpeedTimer.setInterval(1000);
    mSpeedTimer.start();
}

void HttpDownloader::Cancel()
{
    if (!mpReply)
    {
        return;
    }
    mpReply->abort();
}

void HttpDownloader::OnProgressChanged(qint64 bytesDownloaded, qint64 bytesTotal)
{
    mnBytesDownloaded = bytesDownloaded;
    mnBytesTotal = bytesTotal;
}

void HttpDownloader::OnReadyRead()
{
    int used = mTimer.elapsed();
    if (mnBytesDownloaded > 0 && mnBytesTotal > 0 && used > 0)
    {
        int p = mnBytesDownloaded * 100 / mnBytesTotal;
        mnLastSpeed = mnBytesDownloaded * 1000 / used;
        emit SigProgressChanged(p);
    }
    if (mpReply)
    {
        QByteArray data = mpReply->readAll();
    }
}

void HttpDownloader::OnFinished()
{
    QNetworkReply::NetworkError err = mpReply->error();
    mpReply->deleteLater();
    mpReply = nullptr;
    mSpeedTimer.stop();
    if (err == QNetworkReply::NetworkError::NoError)
    {
        emit SigProgressChanged(100);
    }
    emit SigFinished(err == QNetworkReply::NetworkError::NoError);
}

void HttpDownloader::OnSpeedTimer()
{
    if (mnLastSpeed > 0)
    {
        emit SigSpeedChanged(mnLastSpeed);
    }
}
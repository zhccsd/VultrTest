#include "HeadTester.h"

HeadTester::HeadTester(const QString &url, QObject *parent)
    : QObject(parent)
    , mpReply(nullptr)
{
    mRequest.setUrl(QUrl(url));
    QSslConfiguration conf = mRequest.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    mRequest.setSslConfiguration(conf);
}

void HeadTester::Start()
{
    if (mpReply)
    {
        return;
    }
    mTimer.restart();
    mpReply = mNam.head(mRequest);
    connect(mpReply, &QNetworkReply::finished, this, &HeadTester::OnFinished);
}

void HeadTester::OnFinished()
{
    QNetworkReply::NetworkError err = mpReply->error();
    mpReply->deleteLater();
    mpReply = nullptr;
    emit SigFinished(err == QNetworkReply::NetworkError::NoError, mTimer.elapsed());
}
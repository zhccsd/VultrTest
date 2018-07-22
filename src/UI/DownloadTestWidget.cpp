#include "DownloadTestWidget.h"
#include <Download/HttpDownloader.h>

DownloadTestWidget::DownloadTestWidget(const QString &url, QWidget *parent)
    : QWidget(parent)
    , mstrUrl(url)
    , mpDownloader(nullptr)
{
    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    mpbtnStart = new QPushButton("Start");
    connect(mpbtnStart, &QPushButton::clicked, this, &DownloadTestWidget::OnBtnStart);
    layout->addWidget(mpbtnStart);

    mpbtnCancel = new QPushButton("Cancel");
    mpbtnCancel->hide();
    connect(mpbtnCancel, &QPushButton::clicked, this, &DownloadTestWidget::OnBtnCancel);
    layout->addWidget(mpbtnCancel);

    mppgbDownload = new QProgressBar();
    mppgbDownload->setContentsMargins(0, 0, 0, 0);
    mppgbDownload->setTextVisible(false);
    mppgbDownload->setFixedWidth(200);
    mppgbDownload->setRange(0, 100);
    mppgbDownload->setFormat("");
    layout->addWidget(mppgbDownload);

    mplblProgress = new QLabel();
    layout->addWidget(mplblProgress);

    mplblSpeed = new QLabel();
    layout->addWidget(mplblSpeed);

    layout->addStretch(1);
}

void DownloadTestWidget::OnBtnStart()
{
    if (mpDownloader)
    {
        return;
    }
    mpDownloader = new HttpDownloader(mstrUrl);
    connect(mpDownloader, &HttpDownloader::SigProgressChanged, this, &DownloadTestWidget::OnProgressChanged);
    connect(mpDownloader, &HttpDownloader::SigSpeedChanged, this, &DownloadTestWidget::OnSpeedChanged);
    connect(mpDownloader, &HttpDownloader::SigFinished, this, &DownloadTestWidget::OnFinished);
    mpDownloader->Start();

    mpbtnStart->hide();
    mpbtnCancel->show();
}

void DownloadTestWidget::OnBtnCancel()
{
    if (!mpDownloader)
    {
        return;
    }
    mpDownloader->Cancel();
}

void DownloadTestWidget::OnProgressChanged(int p)
{
    mppgbDownload->setValue(p);
    mplblProgress->setText(QString("%1%").arg(p));
}

void DownloadTestWidget::OnSpeedChanged(qint64 speed)
{
    QString strSpeed;
    if (speed < 1024)
    {
        strSpeed = QString("%1Bytes").arg(speed);
    }
    else if (speed < (1024 * 1024))
    {
        strSpeed = QString("%1KiB").arg(speed / 1024.0);
    }
    else if (speed < (1024 * 1024 * 1024))
    {
        strSpeed = QString("%1MiB").arg(speed / 1024.0 / 1024.0);
    }
    else
    {
        strSpeed = QString("%1GiB").arg(speed / 1024.0 / 1024.0 / 1024.0);
    }
    mplblSpeed->setText(QString("Speed:%1/s").arg(strSpeed));
}

void DownloadTestWidget::OnFinished(bool)
{
    mpbtnCancel->hide();
    mpbtnStart->show();
    mpDownloader->deleteLater();
    mpDownloader = nullptr;
}
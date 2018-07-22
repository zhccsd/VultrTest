#ifndef DOWNLOADTESTWIDGET_H
#define DOWNLOADTESTWIDGET_H

class HttpDownloader;
class DownloadTestWidget :public QWidget
{
    Q_OBJECT

public:
    explicit DownloadTestWidget(const QString &url, QWidget *parent = nullptr);

private slots:
    void     OnBtnStart();
    void     OnBtnCancel();
    void     OnProgressChanged(int p);
    void     OnSpeedChanged(qint64 speed);
    void     OnFinished(bool ok);

private:
    QString         mstrUrl;
    QPushButton    *mpbtnStart;
    QPushButton    *mpbtnCancel;
    QProgressBar   *mppgbDownload;
    QLabel         *mplblProgress;
    QLabel         *mplblSpeed;
    HttpDownloader *mpDownloader;
};

#endif
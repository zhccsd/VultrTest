#ifndef HEADTESTWIDGET_H
#define HEADTESTWIDGET_H

class HeadTester;
class HeadTestWidget :public QWidget
{
    Q_OBJECT

public:
    explicit HeadTestWidget(const QString &url, QWidget *parent = nullptr);

public slots:
    void     OnBtnTest();

private slots:
    void     OnFinished(bool ok, int elapsed);

private:
    QString     mstrUrl;
    QLabel     *mplblResult;
    HeadTester *mpTester;
};

#endif
#include "HeadTestWidget.h"
#include <Download/HeadTester.h>

HeadTestWidget::HeadTestWidget(const QString &url, QWidget *parent)
    : QWidget(parent)
    , mstrUrl(url)
    , mpTester(nullptr)
{
    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    QPushButton *btnTest = new QPushButton("Test");
    connect(btnTest, &QPushButton::clicked, this, &HeadTestWidget::OnBtnTest);
    layout->addWidget(btnTest);

    mplblResult = new QLabel;
    layout->addWidget(mplblResult);

    layout->addStretch(1);
}

void HeadTestWidget::OnBtnTest()
{
    if (mpTester)
    {
        return;
    }
    mplblResult->setText("testing...");
    mpTester = new HeadTester(mstrUrl);
    connect(mpTester, &HeadTester::SigFinished, this, &HeadTestWidget::OnFinished);
    mpTester->Start();
}

void HeadTestWidget::OnFinished(bool ok, int elapsed)
{
    mplblResult->setText(QString("%1(%2 ms)").arg(ok ? "success" : "failed").arg(elapsed));
    mpTester->deleteLater();
    mpTester = nullptr;
}
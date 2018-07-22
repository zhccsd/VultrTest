#include "MainWindow.h"
#include "DownloadTestWidget.h"
#include "HeadTestWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(900, 700);

    QWidget *mainWidget = new QWidget;
    this->setCentralWidget(mainWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainWidget->setLayout(mainLayout);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(0);

    QWidget *wgtMenu = new QWidget;
    wgtMenu->setFixedHeight(40);
    QHBoxLayout *lytMenu = new QHBoxLayout;
    wgtMenu->setLayout(lytMenu);
    lytMenu->setContentsMargins(0, 0, 0, 0);
    lytMenu->setSpacing(10);

    mpbtnHeadTestAll = new QPushButton("Head test all");
    lytMenu->addWidget(mpbtnHeadTestAll);
    lytMenu->addStretch(1);

    mpwgtTable = new QTableWidget(this);
    mpwgtTable->setObjectName("mpTableWidget");
    mpwgtTable->setColumnCount(3);
    mpwgtTable->setHorizontalHeaderLabels(
        QStringList()
        << "Location"
        << "Head Test"
        << "Download Test"
        );
    mpwgtTable->setShowGrid(false);
    mpwgtTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    mpwgtTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mpwgtTable->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    mpwgtTable->setSelectionMode(QAbstractItemView::NoSelection);
    mpwgtTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mpwgtTable->setFocusPolicy(Qt::NoFocus);
    mpwgtTable->horizontalHeader()->setDisabled(true);
    mpwgtTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    mpwgtTable->horizontalHeader()->setStretchLastSection(true);
    mpwgtTable->setColumnWidth(0, 150);
    mpwgtTable->setColumnWidth(1, 200);
    mpwgtTable->verticalHeader()->setDefaultSectionSize(35);

    mainLayout->addWidget(wgtMenu);
    mainLayout->addWidget(mpwgtTable);

    AddTest("Frankfurt, DE", "https://fra-de-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Paris, France", "https://par-fr-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Amsterdam, NL", "https://ams-nl-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("London, UK", "https://lon-gb-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("New York (NJ)", "https://nj-us-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Singapore", "https://sgp-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Chicago, Illinois", "https://il-us-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Atlanta, Georgia", "https://ga-us-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Miami, Florida", "https://fl-us-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Tokyo, Japan", "https://hnd-jp-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Dallas, Texas", "https://tx-us-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Seattle, Washington", "https://wa-us-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Silicon Valley, California", "https://sjo-ca-us-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Los Angeles, California", "https://lax-ca-us-ping.vultr.com/vultr.com.100MB.bin");
    AddTest("Sydney, Australia", "https://syd-au-ping.vultr.com/vultr.com.100MB.bin");
}

void MainWindow::AddTest(const QString &name, const QString &url)
{
    int row = mpwgtTable->rowCount();
    mpwgtTable->insertRow(row);

    QTableWidgetItem *itemName = new QTableWidgetItem;
    itemName->setText(name);
    itemName->setToolTip(url);
    mpwgtTable->setItem(row, 0, itemName);

    HeadTestWidget *headTest = new HeadTestWidget(url);
    connect(mpbtnHeadTestAll, &QPushButton::clicked, headTest, &HeadTestWidget::OnBtnTest);
    mpwgtTable->setCellWidget(row, 1, headTest);

    DownloadTestWidget *downloadTest = new DownloadTestWidget(url);
    mpwgtTable->setCellWidget(row, 2, downloadTest);
}
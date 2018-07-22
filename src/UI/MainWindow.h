#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow :public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void     AddTest(const QString &name, const QString &url);

private:
    QPushButton  *mpbtnHeadTestAll;
    QTableWidget *mpwgtTable;
};

#endif
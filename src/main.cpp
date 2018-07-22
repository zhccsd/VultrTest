#include "MainWindow.h"

void main(int argc, char **argv)
{
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    app.exec();
}
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//如果需要改变样式，将这段注释去掉
//    QFile qss(":/styleSheet.qss");
//    if( qss.open(QFile::ReadOnly)) {
//       QString style = QLatin1String(qss.readAll());
//       a.setStyleSheet(style);
//       qss.close();
//    } else {
//      qDebug("Open failed");
//    }
    MainWindow w;
    w.resize(960,640);
    w.show();
    w.setWindowTitle("图像处理");
    w.setWindowIcon(QIcon(":/images/main.png"));
    return a.exec();
}

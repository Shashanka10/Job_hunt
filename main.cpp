#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include<QFile>

QString id;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheetFile(":/resources/image/Hookmark.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}

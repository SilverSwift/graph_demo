#include <QApplication>
#include <QTranslator>

#include "mainwidget.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    qRegisterMetaType<QVector<QPoint>>("VectorOfPoints");

    QTranslator trs;
    if (trs.load(":/demo_ru.qm"))
        app.installTranslator(&trs);

    MainWidget wgt;
    wgt.show();

    return app.exec();
}

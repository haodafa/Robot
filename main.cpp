#include <QApplication>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QSplashScreen>
#include "RobotControl.h"
#include "DataBaseManage.h"
#include "BusinessDataBase.h"
#include "BusinessData.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    int exitCode = 0; // exit

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    // 启动动画
    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/Item/Robott.png"));
    splash->show();

    // 初始化数据库
    if (BusinessDataBase::getInstance()->initDataBase())
    {
        RobotControl robotControl;

        robotControl.initQmlWidget();
        robotControl.createWidget();
        robotControl.initWidgetData();

        splash->close();
        splash->finish(&robotControl);
        delete splash;

        exitCode = app.exec();
    }

    return exitCode;
}

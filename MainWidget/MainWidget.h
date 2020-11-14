#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "RCQmlWidgetHolder.h"
#include "ui_MainWidget.h"
#include "BaseDataInfo.h"


#pragma execution_character_set("utf-8")

class UserManagement;

class MainWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(UserManagement *userManagement READ getUserManagement CONSTANT)

public:
    MainWidget(QWidget* parent = Q_NULLPTR);
    ~MainWidget();

Q_SIGNALS:
    void signalLogout();

public:
    // 初始化窗口数据
    void initWidgetData();

    // 控制窗口显示和隐藏
    void controlWidgetShowHide(bool bShow);

    UserManagement *getUserManagement();

    Q_INVOKABLE void qmlCloseBtnClicked();

    Q_INVOKABLE void qmlMinBtnClicked();

    Q_INVOKABLE void qmlLogoutClicked();

private:
    void clearWidgetData();

private:
    Ui::MainWidget ui;

    RCQmlWidgetHolder* m_QmlWidgetHolder;

    QVBoxLayout *_centralLayout;
    
    QObject *m_pRoot;                           // qml中Root

    UserManagement *m_pUserManagement;
};

#endif // MAINWINDOW_H

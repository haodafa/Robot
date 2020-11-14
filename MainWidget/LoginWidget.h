#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QQmlApplicationEngine>
#include "BaseDataInfo.h"

class RCQmlWidgetHolder;

#pragma execution_character_set("utf-8")

//
//   作者：guokai
//   创建时间：2020-09-27
//   描述 : 登录界面相关类
//
class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

    Q_INVOKABLE bool qmlBtnLoginClicked(QString strUserID, QString strUserPassword, bool bRememberPassword, bool bAutoLogin);

Q_SIGNALS:
    // 登录成功信号
    void signalLoginSucceed();

public:
    // 初始化窗口数据
    void initWidgetData();

    // 清空窗口数据
    void clearWidgetData();

    // 控制窗口的显示和隐藏
    void controlWidgetShowHide(bool bShow);

    // 控制托盘菜单的状态
    void setTrayMenuState(bool bState);

    void loaderQmlWidget();

private Q_SLOTS:
    // 托盘图标活动槽函数
    void slotTrayIconAction(QSystemTrayIcon::ActivationReason reason);

    // 登录菜单点击槽函数
    void slotLoginMenuAction();

private:
    // 初始化托盘菜单
    void initTrayMenu();

    // 获取用户登录信息
    bool getUserLoginInfo();

private:
    RCQmlWidgetHolder *m_pQmlWidgetHolder;

    QMenu* m_pLoginTrayMenu;					// 登录托盘菜单
    QSystemTrayIcon* m_pLoginTray;				// 登录托盘

    QObject *m_pRoot;                           // qml中Root
};

#endif // LOGINWIDGET_H

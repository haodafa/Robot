#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <QWidget>
#include <QApplication>
#include <QQmlEngine>

class LoginWidget;
class MainWidget;

class RobotControl: public QWidget
{
public:
    RobotControl(QWidget* parent = Q_NULLPTR);
    ~RobotControl();

public:
    // 创建窗体
    void createWidget();

    // 初始化数据窗口
    void initWidgetData();

    // 初始化QML窗体
    void initQmlWidget();

private Q_SLOTS:
    // 登录成功槽函数
    void slotLoginSucceed();

    void slotLogout();

private:
    LoginWidget *m_pLoginWidget;        // 登录窗口
    MainWidget *m_pMainWidget;          // 主窗口
};

#endif // ROBOTCONTROL_H

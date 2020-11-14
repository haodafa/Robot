#include "RobotControl.h"
#include <QSettings>
#include <QCoreApplication>
#include <QTranslator>
#include <QDebug>
#include "LoginWidget.h"
#include "MainWidget.h"
#include "BusinessData.h"
#include "BaseDataInfo.h"
#include "BusinessDataBase.h"
#include "ReadJsonFlie.h"
#include "BusinessLogic.h"
#include "UserManagement.h"


static QObject* qmlBusinessDataSingletonFactory(QQmlEngine *engine,QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return BusinessData::getInstance();
}


static QObject* qmlBusinessLogicSingletonFactory(QQmlEngine *engine,QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return BusinessLogic::getInstance();
}


RobotControl::RobotControl(QWidget *parent)
    : QWidget(parent)
    , m_pLoginWidget(nullptr)
    , m_pMainWidget(nullptr)
{

}


RobotControl::~RobotControl()
{
    if (nullptr != m_pMainWidget)
    {
        delete m_pMainWidget;
        m_pMainWidget = nullptr;
    }

    if (nullptr != m_pLoginWidget)
    {
        delete m_pLoginWidget;
        m_pLoginWidget = nullptr;
    }
}


void RobotControl::createWidget()
{
    m_pLoginWidget = new LoginWidget();

    m_pMainWidget = new MainWidget();

    connect(m_pLoginWidget, &LoginWidget::signalLoginSucceed, this, &RobotControl::slotLoginSucceed);

    connect(m_pMainWidget, &MainWidget::signalLogout, this, &RobotControl::slotLogout);
}


void RobotControl::initWidgetData()
{
    ReadJsonFlie::getInstance()->readLeftFunBtnInfo();

    if(nullptr != m_pLoginWidget)
    {
        m_pLoginWidget->initWidgetData();
        m_pLoginWidget->controlWidgetShowHide(true);
    }

    if(nullptr != m_pMainWidget)
    {
        m_pMainWidget->controlWidgetShowHide(false);
    }
}


void RobotControl::initQmlWidget()
{
    qmlRegisterSingletonType<BusinessData>("BusinessData", 1, 0, "BusinessData", qmlBusinessDataSingletonFactory);
    qmlRegisterSingletonType<BusinessLogic>("BusinessLogic", 1, 0, "BusinessLogic", qmlBusinessLogicSingletonFactory);

    qmlRegisterUncreatableType<QmlObjectListModel>("QRobotControl", 1, 0, "ObjectList","Reference only");
    qmlRegisterUncreatableType<BaseData::UserLoginInfo>("BaseData", 1, 0, "UserLoginInfo","Reference only");
    qmlRegisterType<BaseData::UserInfo>("BaseData", 1, 0, "UserInfo");
    qmlRegisterType<BaseData::FactDataInfo>("BaseData", 1, 0, "FactDataInfo");
    qmlRegisterType<BaseData::FactGroupDataInfo>("BaseData", 1, 0, "FactGroupDataInfo");
    qmlRegisterUncreatableType<BaseData::FunBtnInfo>("BaseData", 1, 0, "FunBtnInfo","Reference only");
}


void RobotControl::slotLoginSucceed()
{
    m_pMainWidget->initWidgetData();
    m_pMainWidget->controlWidgetShowHide(true);
    //m_pMainWidget->setMainTrayMenuState(true);

    m_pLoginWidget->controlWidgetShowHide(false);
    m_pLoginWidget->clearWidgetData();
    m_pLoginWidget->setTrayMenuState(false);
}


void RobotControl::slotLogout()
{
    m_pMainWidget->controlWidgetShowHide(false);

    m_pLoginWidget->controlWidgetShowHide(true);
    m_pLoginWidget->setTrayMenuState(true);
    m_pLoginWidget->initWidgetData();
}

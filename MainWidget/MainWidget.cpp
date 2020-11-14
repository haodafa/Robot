#include "MainWidget.h"
#include <QCoreApplication>
#include <QVBoxLayout>
#include "BusinessDataBase.h"
#include "BusinessData.h"
#include "UserManagement.h"


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      _centralLayout(nullptr)
{
    ui.setupUi(this);

    hide();

    m_QmlWidgetHolder = new RCQmlWidgetHolder(this);

    m_QmlWidgetHolder->getApplicationEngine()->rootContext()->setContextProperty ("MainWindow", this);
    m_QmlWidgetHolder->getApplicationEngine()->addImportPath(QStringLiteral("qrc:/qml"));
    m_QmlWidgetHolder->getApplicationEngine()->load(QUrl(QStringLiteral("qrc:/qml/MainWidget.qml")));

    m_pRoot = m_QmlWidgetHolder->getApplicationEngine()->rootObjects().first();

    m_pUserManagement = new UserManagement();

    qmlRegisterUncreatableType<UserManagement>("RobotControl.UserManager",1,0,"UserManagement","Reference only");
}


MainWidget::~MainWidget()
{
    if(nullptr != m_pUserManagement)
    {
        delete m_pUserManagement;
        m_pUserManagement = nullptr;
    }
}


void MainWidget::qmlCloseBtnClicked()
{
    this->close();
}


void MainWidget::qmlMinBtnClicked()
{
    this->showMinimized();
}


void MainWidget::initWidgetData()
{
    m_pUserManagement->getUserInfoList();

    QMetaObject::invokeMethod(m_pRoot, "initQmlWidgetData");
}


void MainWidget::controlWidgetShowHide(bool bShow)
{
    QMetaObject::invokeMethod(m_pRoot, "controlWidgetShowHide", Q_ARG(QVariant, bShow));
}


UserManagement *MainWidget::getUserManagement()
{
    return m_pUserManagement;
}


void MainWidget::qmlLogoutClicked()
{
    clearWidgetData();

    emit signalLogout();
}


void MainWidget::clearWidgetData()
{
    m_pUserManagement->clearWidgetData();
}

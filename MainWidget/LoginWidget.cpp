#include "LoginWidget.h"
#include "RCQmlWidgetHolder.h"
#include <QMenu>
#include "BusinessDataBase.h"
#include "BusinessData.h"

const char* LoginMenuNames[] = {
    "显示主界面",
    "退出"
};

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    initTrayMenu();

    loaderQmlWidget();

    m_pRoot = m_pQmlWidgetHolder->getApplicationEngine()->rootObjects().first();
}


LoginWidget::~LoginWidget()
{
    if (nullptr != m_pLoginTray)
    {
        delete m_pLoginTray;
        m_pLoginTray = nullptr;
    }

    if (nullptr != m_pLoginTrayMenu)
    {
        delete m_pLoginTrayMenu;
        m_pLoginTrayMenu = nullptr;
    }
}


void LoginWidget::initWidgetData()
{
    getUserLoginInfo();

    QMetaObject::invokeMethod(m_pRoot, "initQmlWidgetData");
}


void LoginWidget::clearWidgetData()
{
    QmlObjectListModel *userLoginList = BusinessData::getInstance()->getListModelUserLoginInfo();

    userLoginList->clearAndDeleteContents();
}


void LoginWidget::controlWidgetShowHide(bool bShow)
{
    QMetaObject::invokeMethod(m_pRoot, "controlWidgetShowHide", Q_ARG(QVariant, bShow));
}


void LoginWidget::setTrayMenuState(bool bState)
{
    if (bState)
    {
        m_pLoginTray->show();
    }
    else
    {
        m_pLoginTray->hide();
    }
}


void LoginWidget::slotTrayIconAction(QSystemTrayIcon::ActivationReason reason)
{
    if (QSystemTrayIcon::DoubleClick == reason)
    {
        controlWidgetShowHide(true);
        setWindowState(Qt::WindowNoState);
    }
}


void LoginWidget::slotLoginMenuAction()
{
    QAction* action = qobject_cast<QAction*>(QObject::sender());

    if (LoginMenuNames[action->data().toInt()] == tr("显示主界面")) {
        controlWidgetShowHide(true);
        setWindowState(Qt::WindowNoState);
    }

    if (LoginMenuNames[action->data().toInt()] == tr("退出")) {
        QApplication::instance()->exit(0);
    }
}


void LoginWidget::initTrayMenu()
{
    m_pLoginTray = new QSystemTrayIcon();
    m_pLoginTrayMenu = new QMenu();

    // ?趨??????????????????????png??·??
    m_pLoginTray->setIcon(QIcon(QPixmap(":/Item/RobotControl.ico")));

    m_pLoginTrayMenu->setStyleSheet("QMenu{background-color:#FFFFFF;}\
                                    QMenu::item {padding:5px 25px;}\
                                    QMenu::item:selected {background-color:#D4D4D4;}");

    m_pLoginTrayMenu->setMinimumWidth(180);

    for (int i = 0, end = ARRAY_SIZE(LoginMenuNames); i < end; i++)
    {
        const char* LoginMenuName = LoginMenuNames[i];
        QAction* action = new QAction(this);
        action->setText(LoginMenuName);
        action->setData(i);
        connect(action, &QAction::triggered, this, &LoginWidget::slotLoginMenuAction);
        if (i == end - 1) {
            m_pLoginTrayMenu->addSeparator();
        }
        m_pLoginTrayMenu->addAction(action);
    }

    m_pLoginTray->setContextMenu(m_pLoginTrayMenu);
    connect(m_pLoginTray, &QSystemTrayIcon::activated, this, &LoginWidget::slotTrayIconAction);

    m_pLoginTray->show();
}


bool LoginWidget::getUserLoginInfo()
{
    bool bSuccess = false;

    QList<BaseData::UserLoginInfo*> listUserloginInfo;

    QStringList listUserLoginID;

    if (BusinessDataBase::getInstance()->selectAllUserLoginInfo(listUserloginInfo))
    {
        BusinessData::getInstance()->setUserLoginInfoList(listUserloginInfo);

        int nCount = listUserloginInfo.count();
        for(int nIndex = 0; nIndex < nCount; nIndex++)
        {
            QString userLoginID = listUserloginInfo.at(nIndex)->getUserID();
            listUserLoginID.append(userLoginID);
        }
        BusinessData::getInstance()->setUserLoginIDList(listUserLoginID);

        bSuccess = true;
    }

    return bSuccess;
}


void LoginWidget::loaderQmlWidget()
{
    m_pQmlWidgetHolder = new RCQmlWidgetHolder(this);

    m_pQmlWidgetHolder->getApplicationEngine()->rootContext()->setContextProperty ("userLoginWidget", this);
    m_pQmlWidgetHolder->getApplicationEngine()->addImportPath(QStringLiteral("qrc:/qml"));
    m_pQmlWidgetHolder->getApplicationEngine()->load(QUrl(QStringLiteral("qrc:/qml/LoginWidget.qml")));
}


bool LoginWidget::qmlBtnLoginClicked(QString strUserID, QString strUserPassword, bool bRememberPassword, bool bAutoLogin)
{
    bool bSuccess = false;

    if (BusinessDataBase::getInstance()->LoginPasswordIsCorrect(strUserID, strUserPassword))
    {
        BaseData::UserLoginInfo userLoginInfo;

        userLoginInfo.setUserID(strUserID);
        userLoginInfo.setUserLoginPassword(strUserPassword);
        userLoginInfo.setIsRememberPassword(bRememberPassword);
        userLoginInfo.setIsAutoLogin(bAutoLogin);
        userLoginInfo.setIsLogin(true);

        BusinessDataBase::getInstance()->updateUserLoginInfo(userLoginInfo);

        BaseData::UserInfo curUserInfo;
        BusinessDataBase::getInstance()->selectUserInfo(strUserID, curUserInfo);

        BusinessData::getInstance()->setCurUserInfo(curUserInfo);

        emit signalLoginSucceed();

        bSuccess = true;
    }

    return bSuccess;
}

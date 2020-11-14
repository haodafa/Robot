#include "BusinessDataBase.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include "DataBaseManage.h"

BusinessDataBase* BusinessDataBase::m_pInstance = nullptr;

BusinessDataBase::BusinessDataBase(QObject *parent)
    : QObject(parent)
    ,m_dataBaseManage(nullptr)
{
}


BusinessDataBase::~BusinessDataBase()
{
}


/*---------------------------------------------------------------------------
函数名：getInstance
功能：获取当前类的单实例对象指针
参数：
返回值：BusinessDataBase::BusinessDataBase*
作者：guokai
创建时间：2020-06-30
备注：

---------------------------------------------------------------------------*/
BusinessDataBase* BusinessDataBase::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new BusinessDataBase();
    }

    return m_pInstance;
}


/*---------------------------------------------------------------------------
函数名：initDataBase
功能：初始化数据库
参数：
返回值：bool
作者：guokai
创建时间：2020-06-30
备注：

---------------------------------------------------------------------------*/
bool BusinessDataBase::initDataBase()
{
    bool bSuccess = false;
    if (nullptr == m_dataBaseManage)
    {
        m_dataBaseManage = new DataBaseManage();
    }

    bSuccess = m_dataBaseManage->initDataBase();

    return bSuccess;
}

/*---------------------------------------------------------------------------
函数名：selectAllUserLoginInfo
功能：查找所有用户登录信息
参数：
    QList<BaseData::UserLoginInfo*> listUserLoginInfo[in]：用户登录信息列表
返回值：bool
作者：guokai
创建时间：2020-07-01
备注：

---------------------------------------------------------------------------*/
bool BusinessDataBase::selectAllUserLoginInfo(QList<BaseData::UserLoginInfo*> &listUserLoginInfo)
{
    bool bSuccess = false;

    QSqlQuery query(QSqlDatabase::database("sqlite"));

    QString queryString =
        QString("select * from user where LoginFlag = 1");

    if (query.exec(queryString))
    {
        int nIndexID = query.record().indexOf("id");
        int nIndexPassword = query.record().indexOf("pswd");
        int nIndexIsLogin = query.record().indexOf("LoginFlag");
        int nIndexRemember = query.record().indexOf("pswdFlag");
        int nIndexAutoLogin = query.record().indexOf("autoLoginFlag");

        while (query.next())
        {
            BaseData::UserLoginInfo *userInfo = new BaseData::UserLoginInfo();

            QString strID = query.value(nIndexID).toString();
            QString strPassword = query.value(nIndexPassword).toString();
            bool bIsLogin = query.value(nIndexIsLogin).toBool();
            bool bIsRemember = query.value(nIndexRemember).toBool();
            bool bAutoLogin = query.value(nIndexAutoLogin).toBool();

            userInfo->setUserID(strID);
            userInfo->setUserLoginPassword(strPassword);
            userInfo->setIsLogin(bIsLogin);
            userInfo->setIsRememberPassword(bIsRemember);
            userInfo->setIsAutoLogin(bAutoLogin);

            listUserLoginInfo.append(userInfo);

            bSuccess = true;
        }
    }

    return bSuccess;
}


/*---------------------------------------------------------------------------
函数名：LoginPasswordIsCorrect
功能：登录密码是否正确
参数：
    const QString & strUserID[in]：用户名
    QString & strPassword[in]：密码
返回值：bool
作者：guokai
创建时间：2020-07-01
备注：

---------------------------------------------------------------------------*/
bool BusinessDataBase::LoginPasswordIsCorrect(const QString& strUserID, QString& strPassword)
{
    bool bSuccess = false;

    QSqlQuery query(QSqlDatabase::database("sqlite"));

    QString queryString =
        QString("select pswd from user where id = '%1'").arg(strUserID);

    if (query.exec(queryString))
    {
        int nIndexPassword = query.record().indexOf("pswd");

        while (query.next())
        {
            QString p_strPassword = query.value(nIndexPassword).toString();

            if (p_strPassword == strPassword)
            {
                bSuccess = true;
            }
        }
    }

    return bSuccess;
}


/*---------------------------------------------------------------------------
函数名：updateUserLoginInfo
功能：更新用户登录信息
参数：
    BaseData::UserLoginInfo userLoginInfo[in]：用户登录信息
返回值：bool
作者：guokai
创建时间：2020-07-01
备注：

---------------------------------------------------------------------------*/
bool BusinessDataBase::updateUserLoginInfo(BaseData::UserLoginInfo userLoginInfo)
{
    bool bSuccess = false;

    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryString =
        QString("update user set LoginFlag = '%1',pswdFlag = '%2',autoLoginFlag = '%3' where id = '%4'")
                .arg(userLoginInfo.getIsLogin())
                .arg(userLoginInfo.getIsRememberPassword())
                .arg(userLoginInfo.getIsAutoLogin())
                .arg(userLoginInfo.getUserID());

    if (query.exec(queryString))
    {
        bSuccess = true;
    }

    return bSuccess;
}


/*---------------------------------------------------------------------------
函数名：selectAllUserInfo
功能：查找所有的用户信息
参数：
    QList<BaseData::UserInfo> & listUserInfo[in/out]：用户信息列表
返回值：bool
作者：guokai
创建时间：2020-09-07
备注：

---------------------------------------------------------------------------*/
bool BusinessDataBase::selectAllUserInfo(QList<BaseData::UserInfo*> &listUserInfo)
{
    bool bSuccess = false;

    QSqlQuery query(QSqlDatabase::database("sqlite"));

    QString queryString =
        QString("select * from user");

    if (query.exec(queryString))
    {
        int nIndexID = query.record().indexOf("id");
        int nIndexExual = query.record().indexOf("exual");
        int nIndexJob = query.record().indexOf("job");
        int nIndexTypeNmae = query.record().indexOf("typeName");
        int nIndexName = query.record().indexOf("name");
        int nIndexTime = query.record().indexOf("time");
        int nIndexPassword = query.record().indexOf("pswd");

        while (query.next())
        {
            BaseData::UserInfo *userInfo = new BaseData::UserInfo();

            QString strID = query.value(nIndexID).toString();
            QString strExual = query.value(nIndexExual).toString();
            QString strJob = query.value(nIndexJob).toString();
            int nType = query.value(nIndexTypeNmae).toInt();
            QString strName = query.value(nIndexName).toString();
            QString strTime = query.value(nIndexTime).toString();
            QString strPassword = query.value(nIndexPassword).toString();

            userInfo->setUserID(strID);
            userInfo->setUserExual(strExual);
            userInfo->setUserJobType(strJob);
            userInfo->setUserType((BaseData::UserInfo::enumUSERTYPE)nType);
            userInfo->setUserName(strName);
            userInfo->setUserBuildTime(strTime);
            userInfo->setUserPassword(strPassword);

            listUserInfo.append(userInfo);

            bSuccess = true;
        }
    }

    return bSuccess;
}


bool BusinessDataBase::selectUserInfo(QString strID, BaseData::UserInfo &userInfo)
{
    bool bSuccess = false;

    QSqlQuery query(QSqlDatabase::database("sqlite"));

    QString queryString =
        QString("select * from user where id = '%1'").arg(strID);

    if (query.exec(queryString))
    {
        int nIndexID = query.record().indexOf("id");
        int nIndexExual = query.record().indexOf("exual");
        int nIndexJob = query.record().indexOf("job");
        int nIndexTypeNmae = query.record().indexOf("typeName");
        int nIndexName = query.record().indexOf("name");
        int nIndexTime = query.record().indexOf("time");
        int nIndexPassword = query.record().indexOf("pswd");

        while (query.next())
        {
            QString strID = query.value(nIndexID).toString();
            QString strExual = query.value(nIndexExual).toString();
            QString strJob = query.value(nIndexJob).toString();
            int nType = query.value(nIndexTypeNmae).toInt();
            QString strName = query.value(nIndexName).toString();
            QString strTime = query.value(nIndexTime).toString();
            QString strPassword = query.value(nIndexPassword).toString();

            userInfo.setUserID(strID);
            userInfo.setUserExual(strExual);
            userInfo.setUserJobType(strJob);
            userInfo.setUserType((BaseData::UserInfo::enumUSERTYPE)nType);
            userInfo.setUserName(strName);
            userInfo.setUserBuildTime(strTime);
            userInfo.setUserPassword(strPassword);

            bSuccess = true;
        }
    }

    return bSuccess;
}

bool BusinessDataBase::isExistUserID(QString strID)
{
    bool bIsExits = false;

    QSqlQuery query(QSqlDatabase::database("sqlite"));

    QString queryString =
            QString("select * from user where id = '%1'").arg(strID);

    if(query.exec(queryString))
    {
        if(query.next())
        {
            bIsExits = true;
        }
    }

    return bIsExits;
}

// 插入用户信息数据
bool BusinessDataBase::interpositionUserInfoDta(BaseData::UserInfo *userInfo)
{
    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStringForUser =
            QString("insert into user values('%1', '%2', '%3', '%4', '%5','%6','%7','%8','%9','%10')")
            .arg(userInfo->getUserID()).arg(userInfo->getUserPassword()).arg(userInfo->getUserName()).arg(userInfo->getUserExual())
            .arg(userInfo->getUserJobType()).arg(userInfo->getUserType()).arg(0).arg(0).arg(0).arg(userInfo->getUserBuildTime());

    if(query.exec(queryStringForUser))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 更新用户信息数据
bool BusinessDataBase::updateUserInfoData(BaseData::UserInfo *userInfo)
{
    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryString =
            QString("update user set name = '%1',pswd = '%2',job = '%3',typeName = '%4',exual = '%5',pswdFlag = '%6' ,LoginFlag = '%7',autoLoginFlag = '%8',time = '%9' where id = '%10'")
            .arg(userInfo->getUserName()).arg(userInfo->getUserPassword()).arg(userInfo->getUserJobType()).arg(userInfo->getUserType())
            .arg(userInfo->getUserExual()).arg(0).arg(0).arg(0).arg(userInfo->getUserBuildTime()).arg(userInfo->getUserID());

    if(query.exec(queryString))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 删除用户信息数据
bool BusinessDataBase::deleteUserInfoData(QString strID)
{
    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryString =
            QString("delete from user where id = '%1'").arg(strID);

    if(query.exec(queryString))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool BusinessDataBase::passContextSelectUserInfo(UserManagement::SEARCHUSERTYPE enumSearchType, QString strContext, QList<BaseData::UserInfo*> &listUserInfo)
{
    bool bSuccess = false;

    QSqlQuery query(QSqlDatabase::database("sqlite"));

    QString queryString;

    if(enumSearchType == UserManagement::SEARCHUSERTYPE::SEARCH_NAME)
    {
        queryString = QString("select * from user where name like '%%1%'").arg(strContext);
    }
    else if(enumSearchType == UserManagement::SEARCHUSERTYPE::SEARCH_ID)
    {
        queryString = QString("select * from user where id like '%%1%'").arg(strContext);
    }
    else if(enumSearchType == UserManagement::SEARCHUSERTYPE::SEARCH_JOB)
    {
        queryString = QString("select * from user where job like '%%1%'").arg(strContext);
    }

    if (query.exec(queryString))
    {
        int nIndexID = query.record().indexOf("id");
        int nIndexExual = query.record().indexOf("exual");
        int nIndexJob = query.record().indexOf("job");
        int nIndexTypeNmae = query.record().indexOf("typeName");
        int nIndexName = query.record().indexOf("name");
        int nIndexTime = query.record().indexOf("time");
        int nIndexPassword = query.record().indexOf("pswd");

        while (query.next())
        {
            BaseData::UserInfo *userInfo = new BaseData::UserInfo();

            QString strID = query.value(nIndexID).toString();
            QString strExual = query.value(nIndexExual).toString();
            QString strJob = query.value(nIndexJob).toString();
            int nType = query.value(nIndexTypeNmae).toInt();
            QString strName = query.value(nIndexName).toString();
            QString strTime = query.value(nIndexTime).toString();
            QString strPassword = query.value(nIndexPassword).toString();

            userInfo->setUserID(strID);
            userInfo->setUserExual(strExual);
            userInfo->setUserJobType(strJob);
            userInfo->setUserType((BaseData::UserInfo::enumUSERTYPE)nType);
            userInfo->setUserName(strName);
            userInfo->setUserBuildTime(strTime);
            userInfo->setUserPassword(strPassword);

            listUserInfo.append(userInfo);

            bSuccess = true;
        }
    }

    return bSuccess;
}

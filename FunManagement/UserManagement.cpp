#include "UserManagement.h"
#include "BusinessDataBase.h"
#include "BusinessData.h"
#include <QDebug>
#include <QDate>
#include <QTime>


UserManagement::UserManagement(QObject *parent)
    : QObject(parent)
{

}


int UserManagement::newUserInfo(QVariant varUserInfo)
{
    // 0表示成功 -1表示保存失败 -2表示已存在该用户
    int nState = 0;

    BaseData::UserInfo *userInfo = varUserInfo.value<BaseData::UserInfo*>();

    if(!BusinessDataBase::getInstance()->isExistUserID(userInfo->getUserID()))
    {
        userInfo->setUserBuildTime(QString("%1 %2").arg(QDate::currentDate().toString("yyyy/MM/dd"), QTime::currentTime().toString("HH:mm:ss")));

        if(BusinessDataBase::getInstance()->interpositionUserInfoDta(userInfo))
        {
            BaseData::UserInfo *newUserInfo = new BaseData::UserInfo(*userInfo);

            if(nullptr != newUserInfo)
            {
                QmlObjectListModel *userList = BusinessData::getInstance()->getListModelUserInfo();
                userList->append(newUserInfo);

                nState = 0;
            }
        }
        else
        {
            nState = -1;
        }
    }
    else
    {
        nState = -2;
    }

    return nState;
}


bool UserManagement::modificationUserInfo(QVariant varUserInfo, int nIndex)
{
    bool bSuccess = false;

    if(nIndex >= 0)
    {
        QmlObjectListModel *userList = BusinessData::getInstance()->getListModelUserInfo();

        BaseData::UserInfo *userInfo = varUserInfo.value<BaseData::UserInfo*>();

        BaseData::UserInfo *deleteUserInfo = qobject_cast<BaseData::UserInfo*>(userList->removeAt(nIndex));

        delete deleteUserInfo;
        deleteUserInfo = nullptr;

        BaseData::UserInfo *newUserInfo = new BaseData::UserInfo(*userInfo);

        newUserInfo->setUserBuildTime(QString("%1 %2").arg(QDate::currentDate().toString("yyyy/MM/dd"), QTime::currentTime().toString("HH:mm:ss")));

        if(BusinessDataBase::getInstance()->updateUserInfoData(newUserInfo))
        {
            userList->insert(nIndex, newUserInfo);

            bSuccess = true;
        }
    }

    return bSuccess;
}


QVariant UserManagement::getUserInfo(int nIndex)
{
    QVariant variant;

    if(nIndex >= 0)
    {
        QmlObjectListModel *userList = BusinessData::getInstance()->getListModelUserInfo();

        BaseData::UserInfo* userInfo = qobject_cast<BaseData::UserInfo*>(userList->value(nIndex));

        variant.setValue<BaseData::UserInfo*>(userInfo);
    }

    return  variant;
}


bool UserManagement::deleteUser(int nIndex)
{
    bool bSuccess = false;

    if(nIndex >= 0)
    {
        QmlObjectListModel *userList = BusinessData::getInstance()->getListModelUserInfo();

        BaseData::UserInfo *deleteUserInfo = qobject_cast<BaseData::UserInfo*>(userList->removeAt(nIndex));

        if(BusinessDataBase::getInstance()->deleteUserInfoData(deleteUserInfo->getUserID()))
        {
            if(nullptr != deleteUserInfo)
            {
                delete deleteUserInfo;
                deleteUserInfo = nullptr;
            }

            bSuccess = true;
        }
    }

    return bSuccess;
}


void UserManagement::passConditionSelectUserInfo(QVariant strContent, SEARCHUSERTYPE enumCondition)
{
    QmlObjectListModel *userList = BusinessData::getInstance()->getListModelUserInfo();
    userList->clearAndDeleteContents();

    QList<BaseData::UserInfo*> listUserInfo;

    BusinessDataBase::getInstance()->passContextSelectUserInfo(enumCondition, strContent.toString(),listUserInfo);

    BusinessData::getInstance()->setUserInfoList(listUserInfo);
}


bool UserManagement::getUserInfoList()
{
    bool bSuccess = false;

    QList<BaseData::UserInfo*> listUserInfo;

    if (BusinessDataBase::getInstance()->selectAllUserInfo(listUserInfo))
    {
        BusinessData::getInstance()->setUserInfoList(listUserInfo);

        bSuccess = true;
    }

    return bSuccess;
}


void UserManagement::initWidgetData()
{
    getUserInfoList();
}

void UserManagement::clearWidgetData()
{
    QmlObjectListModel *userList = BusinessData::getInstance()->getListModelUserInfo();
    userList->clearAndDeleteContents();
}

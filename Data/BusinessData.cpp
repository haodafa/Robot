#include "BusinessData.h"
#include <QQmlEngine>
#include <QDebug>

BusinessData* BusinessData::m_pInstance = nullptr;

BusinessData::BusinessData(QObject *parent)
    : QObject(parent)
{

}


BusinessData::~BusinessData()
{
}


/*---------------------------------------------------------------------------
函数名：getInstance
功能：获取单例类的实例
参数：
返回值：BusinessData::BusinessData*
作者：guokai
创建时间：2020-09-18
备注：

---------------------------------------------------------------------------*/
BusinessData* BusinessData::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new BusinessData();
    }
    return m_pInstance;
}


void BusinessData::setUserLoginInfoList(QList<BaseData::UserLoginInfo*> listLoginInfo)
{
    m_listModelUserLoginInfo.clear();

    QList<BaseData::UserLoginInfo*> listUserLoginInfo = listLoginInfo;

    int nCount = listUserLoginInfo.count();
    for(int nIndex = 0; nIndex < nCount; nIndex++)
    {
        BaseData::UserLoginInfo* userLoginInfo = listUserLoginInfo.at(nIndex);
        m_listModelUserLoginInfo.append(userLoginInfo);
    }
}


QList<BaseData::UserLoginInfo*> BusinessData::getUserLoginInfoList()
{
    QList<BaseData::UserLoginInfo*> listUserLoginInfo;

    int nCount = m_listModelUserLoginInfo.count();

    for(int nIndex = 0; nIndex < nCount; nIndex++)
    {
        BaseData::UserLoginInfo* userLoginInfo = static_cast<BaseData::UserLoginInfo*>(m_listModelUserLoginInfo[nIndex]);
        listUserLoginInfo.append(userLoginInfo);
    }

    return listUserLoginInfo;
}


void BusinessData::setUserLoginIDList(QStringList list)
{
    m_listUserLoginID.clear();

    m_listUserLoginID = list;
    emit signaltUserLoginIDListChange();
}


QStringList BusinessData::getUserLoginIDList()
{
    return m_listUserLoginID;
}


QmlObjectListModel *BusinessData::getListModelUserLoginInfo()
{
    return &m_listModelUserLoginInfo;
}


void BusinessData::setFunBtnIDList(QStringList listFunBtnID)
{
    m_listFunBtnID = listFunBtnID;

    emit signalLeftBtnChange();
}

QStringList BusinessData::getFunBtnIDList()
{
    return m_listFunBtnID;
}


void BusinessData::setIDToFunBtnInfoMap(QMap<QString, BaseData::FunBtnInfo*> mapValue)
{
    m_mapIDToFunBtnInfo = mapValue;
}


QMap<QString, BaseData::FunBtnInfo*> BusinessData::getIDToFunBtnInfoMap()
{
    return m_mapIDToFunBtnInfo;
}


void BusinessData::setUserInfoList(QList<BaseData::UserInfo*> listInfo)
{
    m_listModelUserInfo.clear();

    QList<BaseData::UserInfo*> listUserInfo = listInfo;

    int nCount = listUserInfo.count();
    for(int nIndex = 0; nIndex < nCount; nIndex++)
    {
        BaseData::UserInfo* userLoginInfo = listUserInfo.at(nIndex);
        m_listModelUserInfo.append(userLoginInfo);
    }
}


QList<BaseData::UserInfo*> BusinessData::getUserInfoList()
{
    QList<BaseData::UserInfo*> listUserInfo;

    int nCount = m_listModelUserInfo.count();

    for(int nIndex = 0; nIndex < nCount; nIndex++)
    {
        BaseData::UserInfo* userInfo = static_cast<BaseData::UserInfo*>(m_listModelUserInfo[nIndex]);
        listUserInfo.append(userInfo);
    }

    return listUserInfo;
}


QmlObjectListModel *BusinessData::getListModelUserInfo()
{
    return &m_listModelUserInfo;
}


void BusinessData::setCurUserInfo(BaseData::UserInfo userInfo)
{
    m_curUserInfo = userInfo;
}


QVariant BusinessData::getCurUserInfo()
{
    QVariant variant;

    variant.setValue<BaseData::UserInfo*>(&m_curUserInfo);

    return variant;
}

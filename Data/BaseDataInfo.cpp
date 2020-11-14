#include "BaseDataInfo.h"
#include <QDebug>
#include <QQmlEngine>

BaseData::UserLoginInfo::UserLoginInfo()
{

}


BaseData::UserLoginInfo::UserLoginInfo(const UserLoginInfo &userLogin)
{
    m_strUserID = userLogin.m_strUserID;
    m_strPassword = userLogin.m_strPassword;
    m_bIsAutoLogin = userLogin.m_bIsAutoLogin;
    m_bIsRememberPassword = userLogin.m_bIsRememberPassword;
    m_bIsLogin = userLogin.m_bIsLogin;
}


void BaseData::UserLoginInfo::setUserID(QString strUserID)
{
    m_strUserID = strUserID;
}


QString BaseData::UserLoginInfo::getUserID()
{
    return m_strUserID;
}


void BaseData::UserLoginInfo::setUserLoginPassword(QString strPassword)
{
    m_strPassword = strPassword;
}


QString BaseData::UserLoginInfo::getUserLoginPassword()
{
    return m_strPassword;
}


void BaseData::UserLoginInfo::setIsLogin(bool bIsLogin)
{
    m_bIsLogin = bIsLogin;
}


bool BaseData::UserLoginInfo::getIsLogin()
{
    return m_bIsLogin;
}


void BaseData::UserLoginInfo::setIsRememberPassword(bool bIsRememberPassword)
{
    m_bIsRememberPassword = bIsRememberPassword;
}


bool BaseData::UserLoginInfo::getIsRememberPassword()
{
    return m_bIsRememberPassword;
}


void BaseData::UserLoginInfo::setIsAutoLogin(bool bIsAutoLogin)
{
    m_bIsAutoLogin = bIsAutoLogin;
}


bool BaseData::UserLoginInfo::getIsAutoLogin()
{
    return m_bIsAutoLogin;
}


void BaseData::PublicNameAndID::setID(QString strID)
{
    m_strID = strID;
}


QString BaseData::PublicNameAndID::getID()
{
    return m_strID;
}


void BaseData::PublicNameAndID::setName(QString strName)
{
    m_strName = strName;
}


QString BaseData::PublicNameAndID::getName()
{
    return m_strName;
}


void BaseData::FunBtnInfo::setVisible(bool bVisible)
{
    m_bVisible = bVisible;
}


bool BaseData::FunBtnInfo::getVisible()
{
    return m_bVisible;
}


void BaseData::FunBtnInfo::setFilePath(QString strPath)
{
    m_strFilePath = strPath;
}


QString BaseData::FunBtnInfo::getFilePath()
{
    return m_strFilePath;
}


BaseData::UserInfo::UserInfo()
{

}


BaseData::UserInfo::UserInfo(const UserInfo &userInfo)
{
    setUserID(userInfo.m_strUserID);

    m_strName = userInfo.m_strName;
    m_enumType = userInfo.m_enumType;
    m_strExual = userInfo.m_strExual;
    m_strPassword = userInfo.m_strPassword;
    m_strBuildTime = userInfo.m_strBuildTime;
    m_strJobType = userInfo.m_strJobType;
}

void BaseData::UserInfo::operator=(UserInfo userInfo)
{
    setUserID(userInfo.m_strUserID);

    m_strName = userInfo.m_strName;
    m_enumType = userInfo.m_enumType;
    m_strExual = userInfo.m_strExual;
    m_strPassword = userInfo.m_strPassword;
    m_strBuildTime = userInfo.m_strBuildTime;
    m_strJobType = userInfo.m_strJobType;
}


void BaseData::UserInfo::setUserID(QString strUserID)
{
    m_strUserID = strUserID;
    emit signalUserIDChange();
}


QString BaseData::UserInfo::getUserID()
{
    return m_strUserID;
}


void BaseData::UserInfo::setUserPassword(QString strPassword)
{
    m_strPassword = strPassword;
    emit signalUserPasswordChange();
}


QString BaseData::UserInfo::getUserPassword()
{
    return m_strPassword;
}


void BaseData::UserInfo::setUserName(QString strName)
{
    m_strName = strName;
    emit signalUserNameIDChange();
}


QString BaseData::UserInfo::getUserName()
{
    return m_strName;
}


void BaseData::UserInfo::setUserType(BaseData::UserInfo::enumUSERTYPE strType)
{
    m_enumType = strType;
    emit signalUserTypeChange();
}


BaseData::UserInfo::enumUSERTYPE BaseData::UserInfo::getUserType()
{
    return m_enumType;
}


void BaseData::UserInfo::setUserJobType(QString strJobType)
{
    m_strJobType = strJobType;
    emit signalUserJobTypeChange();
}


QString BaseData::UserInfo::getUserJobType()
{
    return m_strJobType;
}


void BaseData::UserInfo::setUserExual(QString strExual)
{
    m_strExual = strExual;
    emit signalUserExualChange();
}


QString BaseData::UserInfo::getUserExual()
{
    return m_strExual;
}


void BaseData::UserInfo::setUserBuildTime(QString strBuildTime)
{
    m_strBuildTime = strBuildTime;
    emit signalUserBuildTimeChange();
}


QString BaseData::UserInfo::getUserBuildTime()
{
    return m_strBuildTime;
}


void BaseData::FactDataInfo::setDataID(QString strID)
{
    m_strID = strID;
}


QString BaseData::FactDataInfo::getDataID()
{
    return m_strID;
}


void BaseData::FactDataInfo::setDataName(QString strName)
{
    m_strName = strName;
}


QString BaseData::FactDataInfo::getDataNmae()
{
    return m_strName;
}


void BaseData::FactDataInfo::setDataValue(QVariant varValue)
{
    m_varValue = varValue;
}


QVariant BaseData::FactDataInfo::getDataValue()
{
    return m_varValue;
}


void BaseData::FactDataInfo::setDataUnit(QString strUnit)
{
    m_strUnit = strUnit;
}


QString BaseData::FactDataInfo::getDataUnit()
{
    return m_strUnit;
}


void BaseData::FactDataInfo::setDataType(BaseData::enumDataType enumType)
{
    m_enumDtaType = enumType;
}


BaseData::enumDataType BaseData::FactDataInfo::getDataType()
{
    return m_enumDtaType;
}


BaseData::FactGroupDataInfo* BaseData::FactGroupDataInfo::getFactGroupData(QString strID)
{
    BaseData::FactGroupDataInfo *pFactGroup = nullptr;

    if(m_mapIDToFactGroupData.contains(strID))
    {
         pFactGroup = m_mapIDToFactGroupData.value(strID);
         QQmlEngine::setObjectOwnership(pFactGroup, QQmlEngine::CppOwnership);
    }

    return pFactGroup;
}


BaseData::FactDataInfo* BaseData::FactGroupDataInfo::getFactData(QString strID)
{
    BaseData::FactDataInfo *pFactData= nullptr;

    if(m_mapIDToFactGroupData.contains(strID))
    {
         pFactData = m_mapIDToFactData.value(strID);
         QQmlEngine::setObjectOwnership(pFactData, QQmlEngine::CppOwnership);
    }

    return pFactData;
}


BaseData::FactDataInfo* BaseData::FactGroupDataInfo::getFactData(QString strID, QString strGroupID)
{
    BaseData::FactGroupDataInfo *pFactGroup = nullptr;
    BaseData::FactDataInfo *pFactData= nullptr;

    if(m_mapIDToFactGroupData.contains(strGroupID))
    {
        pFactGroup = m_mapIDToFactGroupData.value(strGroupID);

        if(nullptr != pFactGroup)
        {
            pFactData = pFactGroup->getFactData(strID);
        }
    }

    return pFactData;
}


void BaseData::FactGroupDataInfo::setFactGroupDataID(QString strID)
{
    m_strGroupID = strID;
}


QString BaseData::FactGroupDataInfo::getFactGroupData()
{
    return m_strGroupID;
}


void BaseData::FactGroupDataInfo::addFactData(QString strID, FactDataInfo* factData)
{
    if(!m_mapIDToFactData.contains(strID))
    {
        m_mapIDToFactData[strID] = factData;
    }
}


void BaseData::FactGroupDataInfo::setFactDataIDList(QStringList strListID)
{
    m_listFactDataID = strListID;
    emit signalFactDataIDChange();
}


QStringList BaseData::FactGroupDataInfo::getFactDataIDList()
{
    return m_listFactDataID;
}


void BaseData::FactGroupDataInfo::addFactGroupData(QString strID, FactGroupDataInfo* factGroupData)
{
    if(!m_mapIDToFactGroupData.contains(strID))
    {
        m_mapIDToFactGroupData[strID] = factGroupData;
    }
}


void BaseData::FactGroupDataInfo::setFactGroupDataIDList(QStringList strListID)
{
    m_listFactGroupDataID = strListID;
    emit signalFactGroupDataIDChange();
}


QStringList BaseData::FactGroupDataInfo::getFactGroupDataIDList()
{
    return m_listFactGroupDataID;
}

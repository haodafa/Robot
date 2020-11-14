#include "BusinessLogic.h"
#include <QQmlEngine>
#include "BusinessData.h"

BusinessLogic* BusinessLogic::m_pInstance = nullptr;


BusinessLogic::BusinessLogic(QObject *parent) : QObject(parent)
{

}


/*---------------------------------------------------------------------------
函数名：getInstance
功能：获取单例类的实例
参数：
返回值：BusinessLogic::BusinessLogic*
作者：guokai
创建时间：2020-09-18
备注：

---------------------------------------------------------------------------*/
BusinessLogic* BusinessLogic::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new BusinessLogic();
    }
    return m_pInstance;
}


/*---------------------------------------------------------------------------
函数名：getInstance
功能：获取单例类的实例
参数：
    QString strID[in]：功能按键信息ID
返回值：BaseData::FunBtnInfo*
作者：guokai
创建时间：2020-10-14
备注：

---------------------------------------------------------------------------*/
BaseData::FunBtnInfo* BusinessLogic::slotGetLeftFunBtnInfo(QString strID)
{
    BaseData::FunBtnInfo* funBtnInfo = nullptr;

    QMap<QString, BaseData::FunBtnInfo*> mapIDToFunBtnInfo;

    mapIDToFunBtnInfo = BusinessData::getInstance()->getIDToFunBtnInfoMap();

    // 得到ID对应的功能按键信息
    if(mapIDToFunBtnInfo.contains(strID))
    {
        funBtnInfo = mapIDToFunBtnInfo[strID];
        QQmlEngine::setObjectOwnership(funBtnInfo, QQmlEngine::CppOwnership);
    }

    return funBtnInfo;
}


BaseData::enumDataType BusinessLogic::stringToType(QString strType)
{
    QStringList listKnownTypeStrings;
    QList<BaseData::enumDataType>  listKnownTypes;

    listKnownTypeStrings << QStringLiteral("Uint8")
                     << QStringLiteral("Int8")
                     << QStringLiteral("Uint16")
                     << QStringLiteral("Int16")
                     << QStringLiteral("Uint32")
                     << QStringLiteral("Int32")
                     << QStringLiteral("Float")
                     << QStringLiteral("Double")
                     << QStringLiteral("String")
                     << QStringLiteral("Bool");

    listKnownTypes << BaseData::enumDataType::valueTypeUint8
               << BaseData::enumDataType::valueTypeInt8
               << BaseData::enumDataType::valueTypeUint16
               << BaseData::enumDataType::valueTypeInt16
               << BaseData::enumDataType::valueTypeUint32
               << BaseData::enumDataType::valueTypeInt32
               << BaseData::enumDataType::valueTypeFloat
               << BaseData::enumDataType::valueTypeDouble
               << BaseData::enumDataType::valueTypeString
               << BaseData::enumDataType::valueTypeBool;

    for (int nIndex=0; nIndex < listKnownTypeStrings.count(); nIndex++)
    {
        if (!listKnownTypeStrings[nIndex].compare(strType, Qt::CaseInsensitive))
        {
            return listKnownTypes[nIndex];
        }
    }

    return BaseData::enumDataType::valueTypeDouble;
}




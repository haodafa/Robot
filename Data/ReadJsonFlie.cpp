#include "ReadJsonFlie.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "BaseDataInfo.h"
#include "BusinessData.h"
#include "BusinessLogic.h"


ReadJsonFlie* ReadJsonFlie::m_pInstance = nullptr;


ReadJsonFlie::ReadJsonFlie(QObject *parent) : QObject(parent)
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
ReadJsonFlie* ReadJsonFlie::getInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new ReadJsonFlie();
    }
    return m_pInstance;
}


/*---------------------------------------------------------------------------
函数名：getInstance
功能：读取左侧功能按键信息列表
参数：
返回值：bool
作者：guokai
创建时间：2020-09-18
备注：

---------------------------------------------------------------------------*/
bool ReadJsonFlie::readLeftFunBtnInfo()
{
    bool bSuccess = false;

    QFile loadFile(":/LeftFunBtnInfo.json");

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        return bSuccess;
    }

    QByteArray allData = loadFile.readAll();
    loadFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

    if(jsonError.error != QJsonParseError::NoError)
    {
        return bSuccess;
    }

    QJsonArray leftFunBtnInfoArray = jsonDoc.array();

    int nCount = leftFunBtnInfoArray.count();

    QStringList listLeftFunBtn;
    QMap<QString, BaseData::FunBtnInfo*> mapIDToFunBtnInfo;

    for(int nIndex = 0; nIndex < nCount; nIndex++)
    {
        BaseData::FunBtnInfo *pFunBtn = new BaseData::FunBtnInfo();

        QJsonObject dataObject = leftFunBtnInfoArray.at(nIndex).toObject();

        if(dataObject.contains("name") && dataObject.value("name").isString())
        {
            pFunBtn->setName(dataObject.value("name").toString());
        }

        if(dataObject.contains("visible") && dataObject.value("visible").isBool())
        {
            pFunBtn->setVisible(dataObject.value("visible").toBool());
        }

        if(dataObject.contains("qmlFilePath") && dataObject.value("qmlFilePath").isString())
        {
            pFunBtn->setFilePath(dataObject.value("qmlFilePath").toString());
        }

        if(dataObject.contains("id") && dataObject.value("id").isString())
        {
            pFunBtn->setID(dataObject.value("id").toString());

            // 判断是否显示 显示则插入要显示的列表
            if(pFunBtn->getVisible())
            {
                listLeftFunBtn.append(dataObject.value("id").toString());
            }
        }

        if(!mapIDToFunBtnInfo.contains(pFunBtn->getID()))
        {
            mapIDToFunBtnInfo.insert(pFunBtn->getID(), pFunBtn);
        }

        bSuccess = true;
    }

    BusinessData::getInstance()->setIDToFunBtnInfoMap(mapIDToFunBtnInfo);
    BusinessData::getInstance()->setFunBtnIDList(listLeftFunBtn);

    return bSuccess;
}


bool ReadJsonFlie::readFactGroupDataInfo(QString strJsonPath, BaseData::FactGroupDataInfo *pFactGroupData)
{
    bool bSuccess = false;

    QFile loadFile(strJsonPath);

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        return bSuccess;
    }

    QByteArray allData = loadFile.readAll();
    loadFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

    if(jsonError.error != QJsonParseError::NoError)
    {
        return bSuccess;
    }

    QJsonArray factDataArray = jsonDoc.array();

    int nCount = factDataArray.count();

    QStringList listFactDataID;

    for(int nIndex = 0; nIndex < nCount; nIndex++)
    {
        BaseData::FactDataInfo *pFactData = new BaseData::FactDataInfo();

        QJsonObject dataObject = factDataArray.at(nIndex).toObject();

        if(dataObject.contains("id") && dataObject.value("id").isString())
        {
            pFactData->setDataID(dataObject.value("id").toString());
        }

        if(dataObject.contains("name") && dataObject.value("name").isString())
        {
            pFactData->setDataName(dataObject.value("name").toString());
        }

        if(dataObject.contains("unit") && dataObject.value("unit").isString())
        {
            pFactData->setDataUnit(dataObject.value("unit").toString());
        }

        if(dataObject.contains("value") && dataObject.value("value").isString())
        {
            pFactData->setDataValue(QVariant(dataObject.value("value").toString()));
        }

        if(dataObject.contains("type") && dataObject.value("type").isString())
        {
            QString strType = dataObject.value("type").toString();
            pFactData->setDataType(BusinessLogic::getInstance()->stringToType(strType));
        }

        pFactGroupData->addFactData(pFactData->getDataID(), pFactData);
        listFactDataID.append(pFactData->getDataID());

        bSuccess = true;
    }

    pFactGroupData->setFactDataIDList(listFactDataID);

    return bSuccess;
}


bool ReadJsonFlie::readAllFactGroupDataInfo(BaseData::FactGroupDataInfo *pFactGroupData)
{
    bool bSuccess = false;

    QFile loadFile("");

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        return bSuccess;
    }

    QByteArray allData = loadFile.readAll();
    loadFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

    if(jsonError.error != QJsonParseError::NoError)
    {
        return bSuccess;
    }

    QJsonArray factGroupDataArray = jsonDoc.array();

    int nCount = factGroupDataArray.count();

    for(int nIndex = 0; nIndex < nCount; nIndex++)
    {

    }

    return bSuccess;
}

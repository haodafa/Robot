#include "Vehicle.h"

Vehicle::Vehicle(QObject *parent)
    : QObject(parent)
    , m_pFactData(nullptr)
{
    m_pFactData = new BaseData::FactGroupDataInfo();

    ReadJsonFlie::getInstance()->readFactGroupDataInfo("qrc:/BaseFactDataInfo.json",m_pFactData);

    ReadJsonFlie::getInstance()->readAllFactGroupDataInfo(m_pFactData);
}


Vehicle::~Vehicle()
{
    if(nullptr != m_pFactData)
    {
        delete m_pFactData;
        m_pFactData = nullptr;
    }
}


BaseData::FactGroupDataInfo *Vehicle::getFactData()
{
    return m_pFactData;
}

#include "VehicleManager.h"

VehicleManager::VehicleManager(QObject *parent)
    : QObject(parent)
    , m_pActiveVehicle(nullptr)
{


}



Vehicle *VehicleManager::getActiveVehicle()
{
    return m_pActiveVehicle;
}

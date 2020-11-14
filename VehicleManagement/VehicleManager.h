#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include <QObject>
#include "Vehicle.h"

class VehicleManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Vehicle *activeVehicle READ getActiveVehicle CONSTANT)

public:
    explicit VehicleManager(QObject *parent = nullptr);

public:
    Vehicle *getActiveVehicle();

signals:

private:
    Vehicle *m_pActiveVehicle;

};

#endif // VEHICLEMANAGER_H

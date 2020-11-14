#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include "ReadJsonFlie.h"
#include "BaseDataInfo.h"

class Vehicle : public QObject
{
    Q_OBJECT

    Q_PROPERTY(BaseData::FactGroupDataInfo *factData READ getFactData CONSTANT)

public:
    explicit Vehicle(QObject *parent = nullptr);
    ~Vehicle();

public:
    BaseData::FactGroupDataInfo *getFactData();

signals:

private:
    BaseData::FactGroupDataInfo *m_pFactData;

};

#endif // VEHICLE_H

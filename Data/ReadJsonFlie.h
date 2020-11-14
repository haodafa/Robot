#ifndef READJSONFLIE_H
#define READJSONFLIE_H

#include <QObject>
#include "BaseDataInfo.h"


class ReadJsonFlie : public QObject
{
    Q_OBJECT
public:
    explicit ReadJsonFlie(QObject *parent = nullptr);

    //获取当前类的单实例对象指针
    static ReadJsonFlie* getInstance();

private:
    static ReadJsonFlie* m_pInstance;

public:
    bool readLeftFunBtnInfo();

    bool readFactGroupDataInfo(QString strJsonPath, BaseData::FactGroupDataInfo *pFactGroupData);

    bool readAllFactGroupDataInfo(BaseData::FactGroupDataInfo *pFactGroupData);
};

#endif // READJSONFLIE_H

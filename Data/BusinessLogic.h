#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include <QObject>
#include "BaseDataInfo.h"


class BusinessLogic : public QObject
{
    Q_OBJECT
public:
    explicit BusinessLogic(QObject *parent = nullptr);

    //获取当前类的单实例对象指针
    static BusinessLogic* getInstance();

private:
    static BusinessLogic* m_pInstance;

public Q_SLOTS:
    // 获取左侧功能按键信息槽函数
    BaseData::FunBtnInfo* slotGetLeftFunBtnInfo(QString strID);

public:
    BaseData::enumDataType stringToType(QString strType);

};

#endif // BUSINESSLOGIC_H

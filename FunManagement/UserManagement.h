#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QObject>
#include <QVariant>
#include "BaseDataInfo.h"

class UserManagement : public QObject
{
    Q_OBJECT
    Q_ENUMS(SEARCHUSERTYPE)

public:
    explicit UserManagement(QObject *parent = nullptr);

    enum SEARCHUSERTYPE
    {
       SEARCH_NAME,
       SEARCH_ID,
       SEARCH_JOB,
       SEARCH_TYPE
    };

    // 新建用户信息
    Q_INVOKABLE int newUserInfo(QVariant varUserInfo);

    // 修改用户信息
    Q_INVOKABLE bool modificationUserInfo(QVariant varUserInfo, int nIndex);

    // 获取指定索引的用户信息
    Q_INVOKABLE QVariant getUserInfo(int nIndex);

    // 删除指定索引的用户
    Q_INVOKABLE bool deleteUser(int nIndex);

    // 通过条件查找用户信息
    Q_INVOKABLE void passConditionSelectUserInfo(QVariant strContent, SEARCHUSERTYPE enumCondition);

    // 获取用户信息列表
    Q_INVOKABLE bool getUserInfoList();

    void initWidgetData();

    void clearWidgetData();
};

#endif // USERMANAGEMENT_H

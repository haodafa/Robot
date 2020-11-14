#ifndef BUSINESSDATABASE_H
#define BUSINESSDATABASE_H

#include <QObject>
#include "BaseDataInfo.h"
#include "UserManagement.h"


class DataBaseManage;

class BusinessDataBase : public QObject
{
    Q_OBJECT

public:
    BusinessDataBase(QObject* parent = nullptr);
    ~BusinessDataBase();

private:
    static BusinessDataBase* m_pInstance;

public:
    //获取当前类的单实例对象指针
    static BusinessDataBase* getInstance();

    // 初始化数据库
    bool initDataBase();

    // 查找所有的用户登录信息
    bool selectAllUserLoginInfo(QList<BaseData::UserLoginInfo*> &listUserLoginInfo);

    // 登录密码是否正确
    bool LoginPasswordIsCorrect(const QString& strUserID, QString& strPassword);

    // 更新用户登录信息
    bool updateUserLoginInfo(BaseData::UserLoginInfo userLoginInfo);

    // 查找所有的用户信息
    bool selectAllUserInfo(QList<BaseData::UserInfo*> &listUserInfo);

    // 查找指定ID用户信息
    bool selectUserInfo(QString strID, BaseData::UserInfo &userInfo);

    // 是否存在指定的用户ID
    bool isExistUserID(QString strID);

    // 插入用户信息数据
    bool interpositionUserInfoDta(BaseData::UserInfo *userInfo);

    // 更新用户信息数据
    bool updateUserInfoData(BaseData::UserInfo *userInfo);

    // 删除用户信息数据
    bool deleteUserInfoData(QString strID);

    // 通过类型和内容查找用户信息
    bool passContextSelectUserInfo(UserManagement::SEARCHUSERTYPE enumSearchType, QString strContext, QList<BaseData::UserInfo*> &listUserInfo);


private:
    DataBaseManage* m_dataBaseManage;
};

#endif // BUSINESSDATABASE_H

#ifndef BUSINESSDATA_H
#define BUSINESSDATA_H

#include <QObject>
#include "BaseDataInfo.h"
#include "QmlObjectListModel.h"


class BusinessData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QmlObjectListModel* listModelUserLoginInfo READ getListModelUserLoginInfo CONSTANT)
    Q_PROPERTY(QmlObjectListModel* listModelUserInfo READ getListModelUserInfo CONSTANT)

    Q_PROPERTY(QStringList listUserLoginID READ getUserLoginIDList WRITE setUserLoginIDList NOTIFY signaltUserLoginIDListChange)

    Q_PROPERTY(QStringList listFunBtnID READ getFunBtnIDList NOTIFY signaltUserLoginIDListChange)

    Q_PROPERTY(QVariant curUserInfo READ getCurUserInfo CONSTANT)

public:
    BusinessData(QObject* parent = nullptr);
    ~BusinessData();

private:
    static BusinessData* m_pInstance;

Q_SIGNALS:
    // 用户登录信息列表改变信号
    void signaltUserLoginInfoListChange();

    // 用户登录ID列表改变信号
    void signaltUserLoginIDListChange();

    // 左侧功能按键改变槽函数
    void signalLeftBtnChange();

public:
    //获取当前类的单实例对象指针
    static BusinessData* getInstance();

    // 设置&获取 用户登录信息列表
    void setUserLoginInfoList(QList<BaseData::UserLoginInfo*> listLoginInfo);
    QList<BaseData::UserLoginInfo*> getUserLoginInfoList();

    // 设置&获取 用户登录ID列表
    void setUserLoginIDList(QStringList list);
    QStringList getUserLoginIDList();

    // 获取用户登录信息Model
    QmlObjectListModel *getListModelUserLoginInfo();

    // 设置&获取 功能按键ID列表
    void setFunBtnIDList(QStringList listFunBtnID);
    QStringList getFunBtnIDList();

    // 设置&获取 ID对应的功能按键信息
    void setIDToFunBtnInfoMap(QMap<QString, BaseData::FunBtnInfo*> mapValue);
    QMap<QString, BaseData::FunBtnInfo*> getIDToFunBtnInfoMap();

    // 设置&获取 用户信息列表
    void setUserInfoList(QList<BaseData::UserInfo*> listInfo);
    QList<BaseData::UserInfo*> getUserInfoList();

    // 获取到用户信息modl列表
    QmlObjectListModel *getListModelUserInfo();

    // 设置&获取 当前用户信息
    void setCurUserInfo(BaseData::UserInfo userInfo);
    QVariant getCurUserInfo();

private:
    QStringList  m_listUserLoginID;                                 // 用户登录ID列表
    QmlObjectListModel m_listModelUserLoginInfo;                    // 用户登录信息列表模型

    QMap<QString, BaseData::FunBtnInfo*> m_mapIDToFunBtnInfo;       // ID和功能数据信息对应关系
    QStringList m_listFunBtnID;                                     // 功能按键ID列表

    QmlObjectListModel m_listModelUserInfo;                         // 用户信息列表模型

    BaseData::UserInfo m_curUserInfo;                               // 当前用户信息                                  // 当前用户类型
};

#endif // BUSINESSDATA_H

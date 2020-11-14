#ifndef BASEDATAINFO_H__
#define BASEDATAINFO_H__
/***************************************************************************\
文件名:  BaseDataInfo.h
作者：guokai
创建时间：2020-06-30

<文件描述>
基础数据类，基本的数据结构都在该文件中
\***************************************************************************/
#include <QString>
#include <QObject>
#include <QVariant>
#include <QMap>

#pragma execution_character_set("utf-8")

#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))

namespace BaseData
{
    //
    //   作者：guokai
    //   创建时间：2020-07-02
    //   描述 : 功能按键ID
    //
    const QString gc_strBaseInfo = "BaseInfo";					// 基本信息
    const QString gc_strMapManage = "MapManage";				// 地图管理
    const QString gc_strUserManage = "UserManage";				// 用户管理
    const QString gc_strRobotManage = "RobotManage";			// 机器人管理
    const QString gc_strPathManage = "PathManage";				// 路径管理
    const QString gc_strTaskManage = "TaskManage";				// 任务管理
    const QString gc_strMonitorPointScene = "MonitorPointScene";// 监测点实况
    const QString gc_strDataCentre = "DataCentre";				// 数据中心
    const QString gc_strBaseSet = "BaseSet";					// 基本设置

    //
    //   作者：guokai
    //   创建时间：2020-07-03
    //   描述 : 各种数据ID标识
    //
    const QString gc_strTemperature = "Temperature";
    const QString gc_strHumidity = "Humidity";
    const QString gc_strSpeed = "Speed";
    const QString gc_strHeading = "Heading";
    const QString gc_strDistance = "Distance";
    const QString gc_strRunTime = "RunTime";
    const QString gc_strVoltage = "Voltage";
    const QString gc_strElectricity = "Electricity";

    enum enumDataType
    {
        valueTypeUint8,
        valueTypeInt8,
        valueTypeUint16,
        valueTypeInt16,
        valueTypeUint32,
        valueTypeInt32,
        valueTypeFloat,
        valueTypeDouble,
        valueTypeString,
        valueTypeBool,
    };

    //
    //   作者：guokai
    //   创建时间：2020-07-03
    //   描述 : 用户登录信息类
    //
    class UserLoginInfo : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString strUserID READ getUserID CONSTANT)
        Q_PROPERTY(QString strPassword READ getUserLoginPassword CONSTANT)
        Q_PROPERTY(bool bIsLogin READ getIsLogin CONSTANT)
        Q_PROPERTY(bool bIsRememberPassword READ getIsRememberPassword CONSTANT)
        Q_PROPERTY(bool bIsAutoLogin READ getIsAutoLogin CONSTANT)

    public:
        UserLoginInfo();
        UserLoginInfo(const UserLoginInfo &userLogin);

        // 设置&获取 用户登录ID
        void setUserID(QString strUserID);
        QString getUserID();

        // 设置&获取 用户登录密码
        void setUserLoginPassword(QString strPassword);
        QString getUserLoginPassword();

        // 设置&获取 用户是否登录过
        void setIsLogin(bool bIsLogin);
        bool getIsLogin();

        // 设置&获取 用户是否记住密码
        void setIsRememberPassword(bool bIsRememberPassword);
        bool getIsRememberPassword();

        // 设置&获取 用户是否自动登录
        void setIsAutoLogin(bool bIsAutoLogin);
        bool getIsAutoLogin();

    private:
        QString m_strUserID;			// 用户ID
        QString m_strPassword;			// 用户密码
        bool m_bIsLogin;				// 是否登录
        bool m_bIsRememberPassword;		// 是否记住密码
        bool m_bIsAutoLogin;			// 是否自动登录
    };


    //
    //   作者：guokai
    //   创建时间：2020-07-03
    //   描述 : 用户信息类
    //
    class UserInfo : public QObject
    {
        Q_OBJECT
        Q_ENUMS(enumUSERTYPE)

        Q_PROPERTY(QString strUserID READ getUserID WRITE setUserID NOTIFY signalUserIDChange)
        Q_PROPERTY(QString strUserPassword READ getUserPassword WRITE setUserPassword NOTIFY signalUserPasswordChange)
        Q_PROPERTY(QString strUserName READ getUserName WRITE setUserName NOTIFY signalUserNameIDChange)
        Q_PROPERTY(enumUSERTYPE enumUserType READ getUserType WRITE setUserType NOTIFY signalUserTypeChange)
        Q_PROPERTY(QString strUserJobType READ getUserJobType WRITE setUserJobType NOTIFY signalUserJobTypeChange)
        Q_PROPERTY(QString strUserExual READ getUserExual WRITE setUserExual NOTIFY signalUserExualChange)
        Q_PROPERTY(QString strUserBuildTime READ getUserBuildTime WRITE setUserBuildTime NOTIFY signalUserBuildTimeChange)

    Q_SIGNALS:
        void signalUserIDChange();
        void signalUserPasswordChange();
        void signalUserNameIDChange();
        void signalUserTypeChange();
        void signalUserJobTypeChange();
        void signalUserExualChange();
        void signalUserBuildTimeChange();

    public:
        UserInfo();
        UserInfo(const UserInfo &userInfo);

        void operator=(UserInfo userInfo);

        enum enumUSERTYPE
        {
            USERTYPE_GENERAL,
            USERTYPE_MANAGE,
            USERTYPE_SUPERMANAGE
        };

        // 设置&获取 用户ID
        void setUserID(QString strUserID);
        QString getUserID();

        // 设置&获取 用户密码
        void setUserPassword(QString strPassword);
        QString getUserPassword();

        // 设置&获取 用户名称
        void setUserName(QString strName);
        QString getUserName();

        // 设置&获取 用户类型
        void setUserType(enumUSERTYPE strType);
        enumUSERTYPE getUserType();

        // 设置&获取 用户工作岗位
        void setUserJobType(QString strJobType);
        QString getUserJobType();

        // 设置&获取 用户性别
        void setUserExual(QString strExual);
        QString getUserExual();

        // 设置&获取 用户建立时间
        void setUserBuildTime(QString strBuildTime);
        QString getUserBuildTime();

    private:
        QString m_strUserID;			// 用户ID
        QString m_strName;				// 用户名字
        QString m_strPassword;			// 用户密码
        enumUSERTYPE m_enumType;		// 用户类型
        QString m_strJobType;			// 工作类型
        QString m_strExual;				// 性别
        QString m_strBuildTime;			// 建立时间
    };

    //
    //   作者：guokai
    //   创建时间：2020-07-03
    //   描述 : 机器人信息类
    //
    class RobotInfo : public QObject
    {

    };

    //
    //   作者：guokai
    //   创建时间：2020-09-07
    //   描述 : 任务信息类
    //
    class TaskInfo : public QObject
    {

    };

    //
    //   作者：guokai
    //   创建时间：2020-09-07
    //   描述 : 路径信息类
    //
    class PathInfo : public QObject
    {

    };

    //
    //   作者：guokai
    //   创建时间：2020-09-07
    //   描述 : 地图信息类
    //
    class MapInfo : public QObject
    {

    };

    //
    //   作者：guokai
    //   创建时间：2020-09-07
    //   描述 : 共有的名字和ID类
    //
    class PublicNameAndID : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString strID READ getID CONSTANT)
        Q_PROPERTY(QString strName READ getName CONSTANT)

    public:
        // 设置&获取 ID
        void setID(QString strID);
        QString getID();

        // 设置&获取 名字
        void setName(QString strName);
        QString getName();

    private:
        QString m_strID;		// ID
        QString m_strName;		// 名字
    };

    //
    //   作者：guokai
    //   创建时间：2020-09-07
    //   描述 : 功能按键信息类
    //
    class FunBtnInfo : public PublicNameAndID
    {
        Q_OBJECT

        Q_PROPERTY(bool bVisible READ getVisible CONSTANT)
        Q_PROPERTY(QString strFilePath READ getFilePath CONSTANT)

    public:
        // 设置&获取 是否显示
        void setVisible(bool bVisible);
        bool getVisible();

        // 设置&获取 文件路径
        void setFilePath(QString strPath);
        QString getFilePath();

    private:
        bool m_bVisible = true;
        QString m_strFilePath = "";
    };

    //
    //   作者：guokai
    //   创建时间：2020-09-18
    //   描述 : 实际数据基本信息
    //
    class FactDataInfo : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString strDataID READ getDataID CONSTANT)
        Q_PROPERTY(QString strDataName READ getDataNmae CONSTANT)
        Q_PROPERTY(QVariant strDataValue READ getDataValue WRITE setDataValue NOTIFY factDataValueChange)
        Q_PROPERTY(QString strDataUnit READ getDataUnit CONSTANT)

    Q_SIGNALS:
        void factDataValueChange();

    public:
        // 设置&获取 数据ID
        void setDataID(QString strID);
        QString getDataID();

        // 设置&获取 数据名称
        void setDataName(QString strName);
        QString getDataNmae();

        // 设置&获取 数据值
        void setDataValue(QVariant varValue);
        QVariant getDataValue();

        // 设置&获取 数据单位
        void setDataUnit(QString strUnit);
        QString getDataUnit();

        // 设置&获取 数据类型
        void setDataType(BaseData::enumDataType enumType);
        BaseData::enumDataType getDataType();

    private:
        QString m_strID;							// 数据ID
        QString m_strName;							// 数据名称
        QVariant m_varValue;						// 数据值
        QString m_strUnit;							// 数据单位
        BaseData::enumDataType m_enumDtaType = BaseData::enumDataType::valueTypeUint8;		// 数据类型
    };


    //
    //   作者：guokai
    //   创建时间：2020-09-18
    //   描述 : 实际数据组基本信息
    //
    class FactGroupDataInfo : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QStringList listFactDataID READ getFactDataIDList WRITE setFactDataIDList NOTIFY signalFactDataIDChange)
        Q_PROPERTY(QStringList listFactGroupDataID READ getFactGroupDataIDList WRITE setFactGroupDataIDList NOTIFY signalFactGroupDataIDChange)

    Q_SIGNALS:
        void signalFactDataIDChange();
        void signalFactGroupDataIDChange();

    public:
        // 通过ID获取数据组
        Q_INVOKABLE FactGroupDataInfo* getFactGroupData(QString strID);

        // 通过ID获取数据
        Q_INVOKABLE BaseData::FactDataInfo* getFactData(QString strID);

        // 通过数据ID和组ID获取数据
        Q_INVOKABLE BaseData::FactDataInfo* getFactData(QString strID, QString strGroupID);

        // 设置&获取 数据组ID
        void setFactGroupDataID(QString strID);
        QString getFactGroupData();

        // 添加数据
        void addFactData(QString strID, FactDataInfo* factData);

        // 设置&获取 数据ID列表
        void setFactDataIDList(QStringList strListID);
        QStringList getFactDataIDList();

        // 添加数据组
        void addFactGroupData(QString strID, FactGroupDataInfo* factGroupData);

        // 设置&获取 数据组ID列表
        void setFactGroupDataIDList(QStringList strListID);
        QStringList getFactGroupDataIDList();

    private:
        QString m_strGroupID;

        QMap<QString, FactDataInfo*> m_mapIDToFactData;
        QStringList m_listFactDataID;

        QMap<QString, FactGroupDataInfo*> m_mapIDToFactGroupData;
        QStringList m_listFactGroupDataID;
    };
}

Q_DECLARE_METATYPE(BaseData::UserInfo*)

#endif // BASEDATAINFO_H__

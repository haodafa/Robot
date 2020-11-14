#include "DataBaseManage.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>


DataBaseManage::DataBaseManage(QObject *parent)
    : QObject(parent)
{
}

DataBaseManage::~DataBaseManage()
{
    closeDataBase();
}

/*---------------------------------------------------------------------------
函数名：createDataBase
功能：创建数据库
参数：
返回值：
作者：guokai
创建时间：2020-06-30
备注：

---------------------------------------------------------------------------*/
void DataBaseManage::createDataBase()
{
    QString Filepath = QCoreApplication::applicationDirPath();
    m_dataBase = QSqlDatabase::addDatabase("QSQLITE", "sqlite");
    m_dataBase.setDatabaseName(QString("%1/RobotControl.db").arg(Filepath));

    m_dataBase.setHostName("localhost");        //数据库主机名
    m_dataBase.setUserName("root");             //数据库登陆用户名
    m_dataBase.setPassword("root1234");         //密码
}


/*---------------------------------------------------------------------------
函数名：initDataBase
功能：初始化数据库
参数：
返回值：bool
作者：guokai
创建时间：2020-06-30
备注：

---------------------------------------------------------------------------*/
bool DataBaseManage::initDataBase()
{
    bool bSuccess = true;

    createDataBase();

    if (!openDataBase())
    {
        return false;
    }
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy/MM/dd hh:mm:ss");

    QSqlQuery sql_query(QSqlDatabase::database("sqlite"));

    QString check_flag = "select flag from init_flag where flag = 1";

    QString create_sql = "create table init_flag(flag bool not NULL)";

    QString inster_data = QString("insert into user values('%1', '%2', '%3', '%4', '%5','%6','%7','%8','%9','%10')").arg("admin").arg("admin").arg("admin").arg("男").arg("admin").arg("0").arg("1").arg("0").arg("0").arg(current_date);

    QString insert_sql = "insert into init_flag values (?)";

    if (sql_query.exec(check_flag))
    {
        bSuccess = true;
    }
    else
    {
        /* 创建标志位的表 */
        create_sql = "create table init_flag(flag bool not NULL)";
        if (!sql_query.exec(create_sql))
        {
            qDebug() << sql_query.lastError();
            bSuccess = false;
        }
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(true);

        // 创建用户表
        create_sql = "create table user(id varchar(20) primary key,pswd varchar(20),name varchar(20),exual varchar(20),job varchar(20), typeName int,LoginFlag int, pswdFlag int, autoLoginFlag int,time varchar(20))";
        if (!sql_query.exec(create_sql))
        {
            qDebug() << sql_query.lastError();
            bSuccess = false;
        }
        sql_query.exec(inster_data);

        // 创建机器人表
        create_sql = "create table robot(id varchar(20) primary key,name varchar(20),buy_time varchar(20),IP varchar(20), type varchar(20),run_time varchar(20),run_distiance varchar(20),robotNumber varchar(20),robotVideoRtsp varchar(20),time varchar(20))";
        if (!sql_query.exec(create_sql))
        {
            qDebug() << sql_query.lastError();
            bSuccess = false;
        }
    }

    return bSuccess;
}


/*---------------------------------------------------------------------------
函数名：openDataBase
功能：打开数据库
参数：
返回值：bool
作者：guokai
创建时间：2020-06-30
备注：

---------------------------------------------------------------------------*/
bool DataBaseManage::openDataBase()
{
    if (m_dataBase.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*---------------------------------------------------------------------------
函数名：closeDataBase
功能：关闭数据库
参数：
返回值：void
作者：guokai
创建时间：2020-06-30
备注：

---------------------------------------------------------------------------*/
void DataBaseManage::closeDataBase()
{
    m_dataBase.close();
}

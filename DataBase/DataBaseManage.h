#ifndef DATABASEMANAGE_H__
#define DATABASEMANAGE_H__
/***************************************************************************\
文件名:  DataBaseManage.h
作者：guokai
创建时间：2020-06-30

<文件描述>
数据库管理相关操作
\***************************************************************************/
#include <QObject>
#include <QSqlDatabase>

#pragma execution_character_set("utf-8")

//
//   作者：guokai
//   创建时间：2020-06-30
//   描述 : 数据库管理相关类
//
class DataBaseManage : public QObject
{
    Q_OBJECT

public:
    DataBaseManage(QObject* parent = nullptr);
    ~DataBaseManage();

public:
    // 初始化数据库
    bool initDataBase();

    // 创建数据库
    void createDataBase();

    // 打开数据库
    bool openDataBase();

    //  关闭数据库
    void closeDataBase();

private:
    QSqlDatabase m_dataBase;
};

#endif // DATABASEMANAGE_H__

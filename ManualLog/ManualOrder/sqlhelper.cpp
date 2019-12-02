#include "sqlhelper.h"
#include <QDebug>

bool SqlHelper::fileExists(QString path)
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}
SqlHelper::SqlHelper(const QString& DbPath):database(),sql_query(),max_id(0)
{
        QString truepath;
        if (fileExists(DbPath))
            truepath = DbPath;
        else
            truepath = "/root/sqllitedb/tradelog_vnpy.db";
        database = createDatabase(truepath);

        open();
        if (database.open())
            sql_query = QSqlQuery(database);

}
SqlHelper::~SqlHelper()
{
    if (database.open())
        close();
}

bool SqlHelper::openstatus()
{
    bool retval = false;

    if (database.open())
        retval = true;
    return retval;
}
QSqlDatabase SqlHelper::createDatabase(const QString& DbPath )
{
    // create database
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(DbPath);
//        database.setUserName("");
//        database.setPassword("");
    }
    return database;
}
void SqlHelper::createDataTable(const QString &dml)
{
    QString create_sql = "create table Log (ID int primary key, Type int, Time varchar(32), Content varchar(32), Note varchar(128))";
    if (dml.size()>0)
        create_sql = dml;
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}
void SqlHelper::open()
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "Open database successfully." ;
        // do something
    }
}
void SqlHelper::close()
{
    database.close();
}
int SqlHelper::insert(const QString &cmd)
{


    if(!sql_query.exec(cmd))
    {
        qDebug() << sql_query.lastError();
        return 0;
    }
    else
    {
        database.commit();
        qDebug() << "inserted successfully.";
        return 1;
    }
}
int SqlHelper::remove(const QString &cmd)
{


    if(!sql_query.exec(cmd))
    {
        qDebug() << sql_query.lastError();
        return 0;
    }
    else
    {
        database.commit();
        qDebug() << "deleted successfully.";
        return 1;
    }
}
void SqlHelper::query(const QString &qur)
{


    if(!sql_query.exec(qur))
    {
        qDebug() << sql_query.lastError();
        //return 0;
    }
    else
    {
        qDebug() << "query successfully.";
        //return 1;
    }
}
int SqlHelper::update(const QString &cmd)
{


    if(!sql_query.exec(cmd))
    {
        qDebug() << sql_query.lastError();
        return 0;
    }
    else
    {
        qDebug() << "update successfully.";
        return 1;
    }
}
int SqlHelper::getMaxId(const QString &tabname)
{

    QString select_max_sql = "select max(orderid) from ";
    select_max_sql += tabname;
    sql_query.prepare(select_max_sql);

    qDebug() << "prepared";
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            max_id = sql_query.value(0).toInt();
            qDebug() << QString("max id:%1").arg(max_id);
            return max_id;
        }
    }
}

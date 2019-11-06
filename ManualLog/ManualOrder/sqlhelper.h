#ifndef SQLHELPER_H
#define SQLHELPER_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
//credit:https://blog.csdn.net/Empty_Android/article/details/80438497
class SqlHelper
{
public:
    SqlHelper(const QString& DbPath);
    QSqlDatabase createDatabase(const QString& DbPath);
    void createDataTable(const QString &dml);
    void open();
    void close();
    bool openstatus();
    int insert(const QString &cmd);
    int remove(const QString &cmd);
    int update(const QString &cmd);
    void query(const QString &qur);
    void deleteRecord(const QString &cmd);
    int getMaxId(const QString &tabname);
    ~SqlHelper();

private:
    QSqlDatabase database;
    QSqlQuery sql_query; //bug 需要在方法中重新定义, 不然会出现 "Driver not loaded" 的错误
    int max_id;
};

#endif // SQLHELPER_H

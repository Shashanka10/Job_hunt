#include <QtSql>

class connect{
public:
QSqlDatabase mydb;

void connclose ()
{
mydb.close();
mydb.removeDatabase(QSqlDatabase::defaultConnection);
}


bool connopen()
{
    mydb.open();
    QDir dir("../login_app2");
    QString path = dir.absolutePath()+"/database.db";
    qDebug()<<(path);
    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(path);
    if (mydb.open()){
        qDebug()<<("Successful ");
        return true;
    }else{
    qDebug()<<("Failed");
    return false;
    }
}
};

#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database{

public:
    Database();
    ~Database();
    bool openDB();
    QSqlError lastError();
    QSqlDatabase getDB();
private:
    QSqlDatabase db;
};

#endif // DATABASE_H

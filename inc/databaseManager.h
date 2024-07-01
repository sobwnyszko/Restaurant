#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class DatabaseManager
{
public:
    static DatabaseManager& instance()
    {
        static DatabaseManager instance;
        return instance;
    }

    QSqlDatabase getDatabase()
    {
        return db;
    }

private:
    QSqlDatabase db;

    DatabaseManager()
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("restauracja");
        db.setUserName("userPracownik");
        db.setPassword("147258369");
        db.setConnectOptions();

        if (!db.open()) {
            qDebug() << "Database error occurred:" << db.lastError().text();
        } else {
            qDebug() << "Database connection established!";
        }
    }

    ~DatabaseManager()
    {
        if (db.isOpen()) {
            db.close();
        }
    }

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
};

#endif // DATABASEMANAGER_H

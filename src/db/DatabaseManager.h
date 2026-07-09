#pragma once
#include <QSqlDatabase>
#include <QString>

class DatabaseManager {
public:
    static DatabaseManager& instance();

    bool open(const QString& path = "bookstore.db");
    void close();

    QSqlDatabase& db() { return m_db; }
    bool isOpen() const { return m_db.isOpen(); }

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

private:
    DatabaseManager() = default;
    ~DatabaseManager();

    bool createSchema();   
    bool seedIfEmpty();    

    QSqlDatabase m_db;
};

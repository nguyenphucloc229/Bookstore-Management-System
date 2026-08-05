#pragma once
#include <QSqlDatabase>
#include <QString>

/*
 * DatabaseManager — DESIGN PATTERN: SINGLETON.
 * Phụ trách: Nguyễn Phúc Lộc
 *
 * Toàn bộ ứng dụng dùng chung MỘT kết nối SQLite duy nhất:
 *  - constructor để private nên bên ngoài không tự tạo được thể hiện;
 *  - copy constructor và operator= bị xoá nên không nhân bản được;
 *  - truy cập qua DatabaseManager::instance().
 * Nhờ vậy tránh việc mỗi màn hình tự mở một kết nối riêng gây tốn tài nguyên
 * và tranh chấp khoá tệp cơ sở dữ liệu.
 */
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

#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager& DatabaseManager::instance()
{

    static DatabaseManager s_instance;
    return s_instance;
}

DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::open(const QString& path)
{
    if (m_db.isOpen())
        return true;

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qWarning() << "Không mở được database:" << m_db.lastError().text();
        return false;
    }
    return createSchema() && seedIfEmpty();
}

void DatabaseManager::close()
{
    if (m_db.isOpen())
        m_db.close();
}

bool DatabaseManager::createSchema()
{
    QSqlQuery q(m_db);
    const QStringList ddl = {

        R"(CREATE TABLE IF NOT EXISTS products (
            id           INTEGER PRIMARY KEY AUTOINCREMENT,
            type         TEXT    NOT NULL,
            name         TEXT    NOT NULL,
            price        REAL    NOT NULL CHECK (price >= 0),
            stock_qty    INTEGER NOT NULL DEFAULT 0 CHECK (stock_qty >= 0),
            isbn         TEXT, author TEXT, publisher TEXT, genre TEXT,
            issue_number INTEGER, publish_date TEXT,
            brand        TEXT, category TEXT
        ))",
        R"(CREATE TABLE IF NOT EXISTS customers (
            id     INTEGER PRIMARY KEY AUTOINCREMENT,
            name   TEXT NOT NULL,
            phone  TEXT,
            email  TEXT
        ))",
        R"(CREATE TABLE IF NOT EXISTS orders (
            id          INTEGER PRIMARY KEY AUTOINCREMENT,
            customer_id INTEGER,
            created_at  TEXT NOT NULL,
            total       REAL NOT NULL,
            FOREIGN KEY (customer_id) REFERENCES customers(id)
        ))",
        R"(CREATE TABLE IF NOT EXISTS order_items (
            id           INTEGER PRIMARY KEY AUTOINCREMENT,
            order_id     INTEGER NOT NULL,
            product_id   INTEGER NOT NULL,
            product_name TEXT NOT NULL,
            unit_price   REAL NOT NULL,
            quantity     INTEGER NOT NULL,
            FOREIGN KEY (order_id)   REFERENCES orders(id),
            FOREIGN KEY (product_id) REFERENCES products(id)
        ))"
    };

    for (const QString& sql : ddl) {
        if (!q.exec(sql)) {
            qWarning() << "Lỗi tạo bảng:" << q.lastError().text();
            return false;
        }
    }
    return true;
}

bool DatabaseManager::seedIfEmpty()
{


    return true;
}

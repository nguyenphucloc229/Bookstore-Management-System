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
        qWarning() << "Unable to open database:" << m_db.lastError().text();
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
            email  TEXT,
            point  INTEGER NOT NULL DEFAULT 0,
            rank   TEXT NOT NULL DEFAULT 'Regular'
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
            qWarning() << "Failed to create table:" << q.lastError().text();
            return false;
        }
    }
    return true;
}

bool DatabaseManager::seedIfEmpty()
{
    QSqlQuery q(m_db);

    // Chỉ seed ở lần chạy đầu tiên (bảng products còn rỗng).
    // Nhờ vậy dữ liệu người dùng nhập sau này không bao giờ bị ghi đè.
    if (!q.exec("SELECT COUNT(*) FROM products") || !q.next()) {
        qWarning() << "Không đọc được bảng products:" << q.lastError().text();
        return false;
    }
    if (q.value(0).toInt() > 0) {
        return true;
    }

    const QStringList seed = {
        // ---- Sách (BOOK) ----
        R"(INSERT INTO products (id, type, name, price, stock_qty, isbn, author, publisher, genre)
           VALUES (1,'BOOK','Clean Code',250000,25,'978-0132350884','Robert C. Martin','Prentice Hall','Programming'))",
        R"(INSERT INTO products (id, type, name, price, stock_qty, isbn, author, publisher, genre)
           VALUES (2,'BOOK','The Pragmatic Programmer',320000,18,'978-0201616224','Andrew Hunt','Addison-Wesley','Programming'))",
        R"(INSERT INTO products (id, type, name, price, stock_qty, isbn, author, publisher, genre)
           VALUES (3,'BOOK','Design Patterns',410000,12,'978-0201633610','Erich Gamma','Addison-Wesley','Programming'))",
        R"(INSERT INTO products (id, type, name, price, stock_qty, isbn, author, publisher, genre)
           VALUES (4,'BOOK','How to Win Friends',88000,40,'978-0671027032','Dale Carnegie','Simon & Schuster','Self-help'))",
        // Tồn kho thấp -> để demo cảnh báo sắp hết hàng
        R"(INSERT INTO products (id, type, name, price, stock_qty, isbn, author, publisher, genre)
           VALUES (5,'BOOK','The Alchemist',79000,4,'978-0061122415','Paulo Coelho','HarperOne','Fiction'))",

        // ---- Tạp chí (MAGAZINE) ----
        R"(INSERT INTO products (id, type, name, price, stock_qty, issue_number, publish_date)
           VALUES (6,'MAGAZINE','National Geographic',65000,30,152,'2026-06-01'))",
        R"(INSERT INTO products (id, type, name, price, stock_qty, issue_number, publish_date)
           VALUES (7,'MAGAZINE','Forbes Vietnam',55000,3,89,'2026-07-01'))",

        // ---- Văn phòng phẩm (STATIONERY) ----
        R"(INSERT INTO products (id, type, name, price, stock_qty, brand, category)
           VALUES (8,'STATIONERY','Thien Long TL-027 Pen',5000,200,'Thien Long','Pen'))",
        R"(INSERT INTO products (id, type, name, price, stock_qty, brand, category)
           VALUES (9,'STATIONERY','Campus Notebook 200p',22000,80,'Campus','Notebook'))",
        R"(INSERT INTO products (id, type, name, price, stock_qty, brand, category)
           VALUES (10,'STATIONERY','Deli Stapler',45000,15,'Deli','Office Tool'))",

        // ---- Khách hàng (đủ 3 hạng để demo) ----
        R"(INSERT INTO customers (id, name, phone, email, point, rank)
           VALUES (1,'Tran Thi Binh','0901234567','binh.tran@gmail.com',1250,'Gold'))",
        R"(INSERT INTO customers (id, name, phone, email, point, rank)
           VALUES (2,'Le Minh Cuong','0912345678','cuong.le@gmail.com',640,'Silver'))",
        R"(INSERT INTO customers (id, name, phone, email, point, rank)
           VALUES (3,'Pham Thu Dung','0923456789','dung.pham@gmail.com',180,'Regular'))",
        R"(INSERT INTO customers (id, name, phone, email, point, rank)
           VALUES (4,'Hoang Van Em','0934567890','em.hoang@gmail.com',45,'Regular'))",

        // ---- Đơn hàng mẫu: 2 đơn hôm nay + 2 đơn các ngày trước ----
        // created_at cùng định dạng ISO (có chữ T) mà ứng dụng ghi ra
        R"(INSERT INTO orders (id, customer_id, created_at, total)
           VALUES (1,1,strftime('%Y-%m-%dT%H:%M:%S','now','localtime'),500000))",
        R"(INSERT INTO orders (id, customer_id, created_at, total)
           VALUES (2,NULL,strftime('%Y-%m-%dT%H:%M:%S','now','localtime'),69000))",
        R"(INSERT INTO orders (id, customer_id, created_at, total)
           VALUES (3,2,strftime('%Y-%m-%dT%H:%M:%S','now','localtime','-1 day'),410000))",
        R"(INSERT INTO orders (id, customer_id, created_at, total)
           VALUES (4,3,strftime('%Y-%m-%dT%H:%M:%S','now','localtime','-2 day'),329000))",

        R"(INSERT INTO order_items (order_id, product_id, product_name, unit_price, quantity)
           VALUES (1,1,'Clean Code',250000,2))",
        R"(INSERT INTO order_items (order_id, product_id, product_name, unit_price, quantity)
           VALUES (2,8,'Thien Long TL-027 Pen',5000,5))",
        R"(INSERT INTO order_items (order_id, product_id, product_name, unit_price, quantity)
           VALUES (2,9,'Campus Notebook 200p',22000,2))",
        R"(INSERT INTO order_items (order_id, product_id, product_name, unit_price, quantity)
           VALUES (3,3,'Design Patterns',410000,1))",
        R"(INSERT INTO order_items (order_id, product_id, product_name, unit_price, quantity)
           VALUES (4,4,'How to Win Friends',88000,3))",
        R"(INSERT INTO order_items (order_id, product_id, product_name, unit_price, quantity)
           VALUES (4,6,'National Geographic',65000,1))"
    };

    m_db.transaction();
    for (const QString& sql : seed) {
        if (!q.exec(sql)) {
            qWarning() << "Lỗi seed dữ liệu mẫu:" << q.lastError().text();
            m_db.rollback();
            return false;
        }
    }
    return m_db.commit();
}

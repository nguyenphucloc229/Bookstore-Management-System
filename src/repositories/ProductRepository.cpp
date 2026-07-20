#include "ProductRepository.h"
#include "db/DatabaseManager.h"
#include "models/Book.h"
#include "models/Magazine.h"
#include "models/Stationery.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

// Helper function to map database columns into a ProductData struct
static ProductData mapQueryToData(QSqlQuery& q) {
    ProductData d;
    d.id = q.value("id").toInt();
    d.name = q.value("name").toString();
    d.price = q.value("price").toDouble();
    d.stockQty = q.value("stock_qty").toInt();

    d.isbn = q.value("isbn").toString();
    d.author = q.value("author").toString();
    d.publisher = q.value("publisher").toString();
    d.genre = q.value("genre").toString();

    d.issueNumber = q.value("issue_number").toInt();
    d.publishDate = q.value("publish_date").toString();

    d.brand = q.value("brand").toString();
    d.category = q.value("category").toString();

    return d;
}

int ProductRepository::add(const Product& p) {
    QSqlQuery q(DatabaseManager::instance().db());
    q.prepare("INSERT INTO products (type, name, price, stock_qty, isbn, author, publisher, genre, issue_number, publish_date, brand, category) "
              "VALUES (:type, :name, :price, :stock_qty, :isbn, :author, :publisher, :genre, :issue_number, :publish_date, :brand, :category)");

    q.bindValue(":type", p.getType());
    q.bindValue(":name", p.name());
    q.bindValue(":price", p.price());
    q.bindValue(":stock_qty", p.stockQty());

    if (auto book = dynamic_cast<const Book*>(&p)) {
        q.bindValue(":isbn", book->isbn());
        q.bindValue(":author", book->author());
        q.bindValue(":publisher", book->publisher());
        q.bindValue(":genre", book->genre());
        q.bindValue(":issue_number", QVariant());
        q.bindValue(":publish_date", QVariant());
        q.bindValue(":brand", QVariant());
        q.bindValue(":category", QVariant());
    } else if (auto mag = dynamic_cast<const Magazine*>(&p)) {
        q.bindValue(":isbn", QVariant());
        q.bindValue(":author", QVariant());
        q.bindValue(":publisher", QVariant());
        q.bindValue(":genre", QVariant());
        q.bindValue(":issue_number", mag->issueNumber());
        q.bindValue(":publish_date", mag->publishDate());
        q.bindValue(":brand", QVariant());
        q.bindValue(":category", QVariant());
    } else if (auto st = dynamic_cast<const Stationery*>(&p)) {
        q.bindValue(":isbn", QVariant());
        q.bindValue(":author", QVariant());
        q.bindValue(":publisher", QVariant());
        q.bindValue(":genre", QVariant());
        q.bindValue(":issue_number", QVariant());
        q.bindValue(":publish_date", QVariant());
        q.bindValue(":brand", st->brand());
        q.bindValue(":category", st->category());
    }

    if (!q.exec()) {
        qDebug() << "Add product error:" << q.lastError().text();
        return -1;
    }
    return q.lastInsertId().toInt();
}

bool ProductRepository::update(const Product& p) {
    QSqlQuery q(DatabaseManager::instance().db());
    q.prepare("UPDATE products SET name = :name, price = :price, stock_qty = :stock_qty, "
              "isbn = :isbn, author = :author, publisher = :publisher, genre = :genre, "
              "issue_number = :issue_number, publish_date = :publish_date, "
              "brand = :brand, category = :category WHERE id = :id");

    q.bindValue(":id", p.id());
    q.bindValue(":name", p.name());
    q.bindValue(":price", p.price());
    q.bindValue(":stock_qty", p.stockQty());

    if (auto book = dynamic_cast<const Book*>(&p)) {
        q.bindValue(":isbn", book->isbn());
        q.bindValue(":author", book->author());
        q.bindValue(":publisher", book->publisher());
        q.bindValue(":genre", book->genre());
        q.bindValue(":issue_number", QVariant());
        q.bindValue(":publish_date", QVariant());
        q.bindValue(":brand", QVariant());
        q.bindValue(":category", QVariant());
    } else if (auto mag = dynamic_cast<const Magazine*>(&p)) {
        q.bindValue(":isbn", QVariant());
        q.bindValue(":author", QVariant());
        q.bindValue(":publisher", QVariant());
        q.bindValue(":genre", QVariant());
        q.bindValue(":issue_number", mag->issueNumber());
        q.bindValue(":publish_date", mag->publishDate());
        q.bindValue(":brand", QVariant());
        q.bindValue(":category", QVariant());
    } else if (auto st = dynamic_cast<const Stationery*>(&p)) {
        q.bindValue(":isbn", QVariant());
        q.bindValue(":author", QVariant());
        q.bindValue(":publisher", QVariant());
        q.bindValue(":genre", QVariant());
        q.bindValue(":issue_number", QVariant());
        q.bindValue(":publish_date", QVariant());
        q.bindValue(":brand", st->brand());
        q.bindValue(":category", st->category());
    }

    return q.exec();
}

bool ProductRepository::remove(int id) {
    QSqlQuery q(DatabaseManager::instance().db());
    q.prepare("DELETE FROM products WHERE id = :id");
    q.bindValue(":id", id);
    return q.exec();
}

std::unique_ptr<Product> ProductRepository::findById(int id) {
    QSqlQuery q(DatabaseManager::instance().db());
    q.prepare("SELECT * FROM products WHERE id = :id");
    q.bindValue(":id", id);

    if (q.exec() && q.next()) {
        QString type = q.value("type").toString();
        ProductData d = mapQueryToData(q);
        return ProductFactory::create(type, d);
    }
    return nullptr;
}

std::vector<std::unique_ptr<Product>> ProductRepository::getAll() {
    std::vector<std::unique_ptr<Product>> list;
    QSqlQuery q("SELECT * FROM products", DatabaseManager::instance().db());

    while (q.next()) {
        QString type = q.value("type").toString();
        ProductData d = mapQueryToData(q);
        auto item = ProductFactory::create(type, d);
        if (item) list.push_back(std::move(item));
    }
    return list;
}

std::vector<std::unique_ptr<Product>> ProductRepository::search(const QString& keyword, const QString& type) {
    std::vector<std::unique_ptr<Product>> list;
    QString sql = "SELECT * FROM products WHERE 1=1";

    if (!keyword.isEmpty()) {
        sql += " AND (name LIKE :kw OR author LIKE :kw OR brand LIKE :kw)";
    }
    if (!type.isEmpty()) {
        sql += " AND type = :type";
    }

    QSqlQuery q(DatabaseManager::instance().db());
    q.prepare(sql);

    if (!keyword.isEmpty()) {
        q.bindValue(":kw", "%" + keyword + "%");
    }
    if (!type.isEmpty()) {
        q.bindValue(":type", type);
    }

    if (q.exec()) {
        while (q.next()) {
            QString itemType = q.value("type").toString();
            ProductData d = mapQueryToData(q);
            auto item = ProductFactory::create(itemType, d);
            if (item) list.push_back(std::move(item));
        }
    }
    return list;
}

std::vector<std::unique_ptr<Product>> ProductRepository::lowStock(int threshold) {
    std::vector<std::unique_ptr<Product>> list;
    QSqlQuery q(DatabaseManager::instance().db());
    q.prepare("SELECT * FROM products WHERE stock_qty <= :threshold");
    q.bindValue(":threshold", threshold);

    if (q.exec()) {
        while (q.next()) {
            QString type = q.value("type").toString();
            ProductData d = mapQueryToData(q);
            auto item = ProductFactory::create(type, d);
            if (item) list.push_back(std::move(item));
        }
    }
    return list;
}

bool ProductRepository::decrementStock(int productId, int qty) {
    QSqlQuery q(DatabaseManager::instance().db());
    q.prepare("UPDATE products SET stock_qty = stock_qty - :qty WHERE id = :id AND stock_qty >= :qty");
    q.bindValue(":qty", qty);
    q.bindValue(":id", productId);

    if (q.exec()) {
        return q.numRowsAffected() > 0;
    }
    return false;
}
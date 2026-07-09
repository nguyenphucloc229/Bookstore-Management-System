#include "ProductRepository.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>

// ============================================================
// TODO(Member 2): implement toàn bộ file này.
// Mẫu tham khảo cách viết 1 hàm với QSqlQuery:
//
// int ProductRepository::add(const Product& p) {
//     QSqlQuery q(DatabaseManager::instance().db());
//     q.prepare("INSERT INTO products (type, name, price, stock_qty, ...) "
//               "VALUES (:type, :name, :price, :stock, ...)");
//     q.bindValue(":type", p.getType());
//     q.bindValue(":name", p.name());
//     ...
//     if (!q.exec()) return -1;
//     return q.lastInsertId().toInt();
// }
// Lưu ý: với Book cần dynamic_cast<const Book*>(&p) để lấy isbn/author...
// ============================================================

int ProductRepository::add(const Product& p)
{
    (void)p;
    return -1; // TODO(Member 2)
}

bool ProductRepository::update(const Product& p)
{
    (void)p;
    return false; // TODO(Member 2)
}

bool ProductRepository::remove(int id)
{
    (void)id;
    return false; // TODO(Member 2)
}

std::unique_ptr<Product> ProductRepository::findById(int id)
{
    (void)id;
    return nullptr; // TODO(Member 2)
}

std::vector<std::unique_ptr<Product>> ProductRepository::getAll()
{
    return {}; // TODO(Member 2)
}

std::vector<std::unique_ptr<Product>> ProductRepository::search(const QString& keyword,
                                                                const QString& type)
{
    (void)keyword; (void)type;
    return {}; // TODO(Member 2)
}

std::vector<std::unique_ptr<Product>> ProductRepository::lowStock(int threshold)
{
    (void)threshold;
    return {}; // TODO(Member 2)
}

bool ProductRepository::decrementStock(int productId, int qty)
{
    (void)productId; (void)qty;
    return false; // TODO(Member 2) — nhớ kiểm tra stock_qty >= qty trước khi trừ
}

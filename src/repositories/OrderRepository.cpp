#include "OrderRepository.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>

// TODO(Member 4): implement.
// Gợi ý transaction:
//   auto& db = DatabaseManager::instance().db();
//   db.transaction();
//   ... INSERT INTO orders ... -> lấy lastInsertId()
//   ... INSERT INTO order_items cho từng item ...
//   nếu tất cả OK -> db.commit(); nếu lỗi -> db.rollback();

int OrderRepository::save(const Order& order)
{
    (void)order;
    return -1; // TODO(Member 4)
}

std::unique_ptr<Order> OrderRepository::findById(int id)
{
    (void)id;
    return nullptr; // TODO(Member 4)
}

std::vector<std::unique_ptr<Order>> OrderRepository::getAll()
{
    return {}; // TODO(Member 4)
}

std::vector<std::unique_ptr<Order>> OrderRepository::byDateRange(const QDateTime& from,
                                                                 const QDateTime& to)
{
    (void)from; (void)to;
    return {}; // TODO(Member 4) — Member 5 dùng hàm này cho báo cáo doanh thu
}

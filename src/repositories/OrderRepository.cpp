#include "OrderRepository.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
// TODO(Member 4): implement.
// Gợi ý transaction:
//   auto& db = DatabaseManager::instance().db();
//   db.transaction();
//   ... INSERT INTO orders ... -> lấy lastInsertId()
//   ... INSERT INTO order_items cho từng item ...
//   nếu tất cả OK -> db.commit(); nếu lỗi -> db.rollback();

int OrderRepository::save(const Order& order)
{
    auto& db = DatabaseManager::instance().db();

    if (!db.isOpen()) {
        qWarning() << "Database chua duoc mo";
        return -1;
    }

    if (!db.transaction()) {
        qWarning() << "Khong the bat đau transaction:"
                   << db.lastError().text();
        return -1;
    }

    QSqlQuery orderQuery(db);
    orderQuery.prepare(
        "INSERT INTO orders (customer_id, created_at, total) "
        "VALUES (:customer_id, :created_at, :total)"
        );

    if (order.customerId() == 0) {
        orderQuery.bindValue(":customer_id", QVariant());
    } else {
        orderQuery.bindValue(":customer_id", order.customerId());
    }

    orderQuery.bindValue(
        ":created_at",
        order.createdAt().toString(Qt::ISODate)
        );

    orderQuery.bindValue(":total", order.total());

    if (!orderQuery.exec()) {
        qWarning() << "Khong the luu don hang:"
                   << orderQuery.lastError().text();
        db.rollback();
        return -1;
    }

    const int orderId = orderQuery.lastInsertId().toInt();
    QSqlQuery itemQuery(db);
    itemQuery.prepare(
        "INSERT INTO order_items "
        "(order_id, product_id, product_name, unit_price, quantity) "
        "VALUES (:order_id, :product_id, :product_name, :unit_price, :quantity)"
        );

    for (const OrderItem& item : order.items()) {
        itemQuery.bindValue(":order_id", orderId);
        itemQuery.bindValue(":product_id", item.productId);
        itemQuery.bindValue(":product_name", item.productName);
        itemQuery.bindValue(":unit_price", item.unitPrice);
        itemQuery.bindValue(":quantity", item.quantity);

        if (!itemQuery.exec()) {
            qWarning() << "Khong the luu chi tiet don hang:"
                       << itemQuery.lastError().text();
            db.rollback();
            return -1;
        }
    }

    if (!db.commit()) {
        qWarning() << "Khong the commit don hang:"
                   << db.lastError().text();
        db.rollback();
        return -1;
    }

    return orderId;
}
std::vector<std::unique_ptr<Order>>
OrderRepository::byDateRange(const QDateTime& from,
                             const QDateTime& to)
{
    std::vector<std::unique_ptr<Order>> orders;

    auto& db = DatabaseManager::instance().db();

    if (!db.isOpen()) {
        qWarning() << "Database chưa được mở";
        return orders;
    }

    QSqlQuery orderQuery(db);
    orderQuery.prepare(
        "SELECT id, customer_id, created_at "
        "FROM orders "
        "WHERE created_at >= :from AND created_at <= :to "
        "ORDER BY created_at ASC"
        );

    orderQuery.bindValue(":from", from.toString(Qt::ISODate));
    orderQuery.bindValue(":to", to.toString(Qt::ISODate));

    if (!orderQuery.exec()) {
        qWarning() << "Khong the doc danh sach don hang:"
                   << orderQuery.lastError().text();
        return orders;
    }

    while (orderQuery.next()) {
        const int orderId = orderQuery.value("id").toInt();
        const int customerId = orderQuery.value("customer_id").toInt();

        const QDateTime createdAt = QDateTime::fromString(
            orderQuery.value("created_at").toString(),
            Qt::ISODate
            );

        auto order = std::make_unique<Order>(
            orderId,
            customerId,
            createdAt
            );

        QSqlQuery itemQuery(db);
        itemQuery.prepare(
            "SELECT product_id, product_name, unit_price, quantity "
            "FROM order_items "
            "WHERE order_id = :order_id "
            "ORDER BY id ASC"
            );

        itemQuery.bindValue(":order_id", orderId);

        if (!itemQuery.exec()) {
            qWarning() << "Khong the doc chi tiet don hang:"
                       << itemQuery.lastError().text();
            return {};
        }

        while (itemQuery.next()) {
            OrderItem item;
            item.productId = itemQuery.value("product_id").toInt();
            item.productName = itemQuery.value("product_name").toString();
            item.unitPrice = itemQuery.value("unit_price").toDouble();
            item.quantity = itemQuery.value("quantity").toInt();

            order->addItem(item);
        }

        orders.push_back(std::move(order));
    }

    return orders;
}

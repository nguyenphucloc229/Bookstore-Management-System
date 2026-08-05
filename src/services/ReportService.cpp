#include "ReportService.h"
#include "db/DatabaseManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

QVector<ReportService::RevenuePoint> ReportService::revenueByDay(const QDate& from,
                                                                 const QDate& to)
{
    QVector<RevenuePoint> result;

    QSqlQuery query(DatabaseManager::instance().db());

    query.prepare(
    "SELECT DATE(created_at), "
    "SUM(total), "
    "COUNT(*) "
    "FROM orders "
    "WHERE DATE(created_at) BETWEEN ? AND ? "
    "GROUP BY DATE(created_at) "
    "ORDER BY DATE(created_at)"
);

    query.addBindValue(from.toString("yyyy-MM-dd"));
    query.addBindValue(to.toString("yyyy-MM-dd"));

    if(query.exec())
    {
        while(query.next())
        {
            RevenuePoint p;

            p.label=query.value(0).toString();
            p.revenue=query.value(1).toDouble();
            p.orderCount=query.value(2).toInt();

            result.push_back(p);
        }
    }

    return result;
}
QVector<ReportService::RevenuePoint> ReportService::revenueByMonth(int year)
{
    QVector<RevenuePoint> result;

    QSqlQuery query(DatabaseManager::instance().db());

    query.prepare(
        "SELECT strftime('%m', created_at), "
        "SUM(total), "
        "COUNT(*) "
        "FROM orders "
        "WHERE strftime('%Y', created_at)=? "
        "GROUP BY strftime('%m', created_at) "
        "ORDER BY strftime('%m', created_at)"
    );

    query.addBindValue(QString::number(year));

    if(query.exec())
    {
        while(query.next())
        {
            RevenuePoint p;

            p.label=query.value(0).toString();
            p.revenue=query.value(1).toDouble();
            p.orderCount=query.value(2).toInt();

            result.push_back(p);
        }
    }

    return result;
}
QVector<ReportService::TopProduct> ReportService::topSellingProducts(int limit)
{
    QVector<TopProduct> result;

    QSqlQuery query(DatabaseManager::instance().db());

    query.prepare(
        // MAX(product_name): mỗi order_item lưu tên tại thời điểm bán, nếu sản phẩm
        // được đổi tên thì một product_id có thể có nhiều tên khác nhau. Dùng hàm
        // gộp để kết quả luôn xác định thay vì phụ thuộc SQLite chọn hộ.
        "SELECT product_id, "
        "MAX(product_name), "
        "SUM(quantity), "
        "SUM(quantity*unit_price) "
        "FROM order_items "
        "GROUP BY product_id "
        "ORDER BY SUM(quantity) DESC, MAX(product_name) ASC "
        "LIMIT ?"
    );

    query.addBindValue(limit);

    if(query.exec())
    {
        while(query.next())
        {
            TopProduct p;

            p.productId=query.value(0).toInt();
            p.name=query.value(1).toString();
            p.totalSold=query.value(2).toInt();
            p.totalRevenue=query.value(3).toDouble();

            result.push_back(p);
        }
    }

    return result;
}
double ReportService::totalRevenueToday()
{
    QSqlQuery query(DatabaseManager::instance().db());

    query.exec(
        "SELECT IFNULL(SUM(total),0) "
        "FROM orders "
        "WHERE DATE(created_at)=DATE('now','localtime')"
    );

    if(query.next())
        return query.value(0).toDouble();

    return 0;
}
int ReportService::totalOrdersToday()
{
    QSqlQuery query(DatabaseManager::instance().db());

    query.exec(
        "SELECT COUNT(*) "
        "FROM orders "
        "WHERE DATE(created_at)=DATE('now','localtime')"
    );

    if(query.next())
        return query.value(0).toInt();

    return 0;
}
int ReportService::lowStockCount(int threshold)
{
    QSqlQuery query(DatabaseManager::instance().db());

    query.prepare(
        "SELECT COUNT(*) "
        "FROM products "
        "WHERE stock_qty <= ?"
    );

    query.addBindValue(threshold);

    if(query.exec() && query.next())
        return query.value(0).toInt();

    return 0;
}
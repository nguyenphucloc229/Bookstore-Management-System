#include "ReportService.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>

// TODO(Member 5): implement toàn bộ bằng QSqlQuery + GROUP BY

QVector<ReportService::RevenuePoint> ReportService::revenueByDay(const QDate& from,
                                                                 const QDate& to)
{
    QVector<RevenuePoint> result;

    QSqlQuery query(DatabaseManager::instance().db());

    query.prepare(
        "SELECT DATE(created_at),"
        "SUM(total),"
        "COUNT(*) "
        "FROM orders "
        "WHERE DATE(created_at) BETWEEN ? AND ? "
        "GROUP BY DATE(created_at)"
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
    (void)year;
    return {}; // TODO(Member 5)
}

QVector<ReportService::TopProduct> ReportService::topSellingProducts(int limit)
{
    QVector<TopProduct> result;

    QSqlQuery query(DatabaseManager::instance().db());

    query.prepare(
        "SELECT product_id,"
        "product_name,"
        "SUM(quantity),"
        "SUM(quantity*unit_price)"
        " FROM order_items "
        "GROUP BY product_id "
        "ORDER BY SUM(quantity) DESC "
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

    query.exec("SELECT IFNULL(SUM(total),0) FROM orders");

    if(query.next())
        return query.value(0).toDouble();

    return 0;
}


int ReportService::totalOrdersToday()
{
    return 0; // TODO(Member 5)
}

int ReportService::lowStockCount(int threshold)
{
    (void)threshold;
    return 0; // TODO(Member 5)
}

#include "ReportService.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>

// TODO(Member 5): implement toàn bộ bằng QSqlQuery + GROUP BY

QVector<ReportService::RevenuePoint> ReportService::revenueByDay(const QDate& from,
                                                                 const QDate& to)
{
    (void)from; (void)to;
    return {}; // TODO(Member 5)
}

QVector<ReportService::RevenuePoint> ReportService::revenueByMonth(int year)
{
    (void)year;
    return {}; // TODO(Member 5)
}

QVector<ReportService::TopProduct> ReportService::topSellingProducts(int limit)
{
    (void)limit;
    return {}; // TODO(Member 5)
}

double ReportService::totalRevenueToday()
{
    return 0; // TODO(Member 5)
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

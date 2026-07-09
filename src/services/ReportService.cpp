#include "ReportService.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>



QVector<ReportService::RevenuePoint> ReportService::revenueByDay(const QDate& from,
                                                                 const QDate& to)
{
    (void)from; (void)to;
    return {};
}

QVector<ReportService::RevenuePoint> ReportService::revenueByMonth(int year)
{
    (void)year;
    return {};
}

QVector<ReportService::TopProduct> ReportService::topSellingProducts(int limit)
{
    (void)limit;
    return {};
}

double ReportService::totalRevenueToday()
{
    return 0;
}

int ReportService::totalOrdersToday()
{
    return 0;
}

int ReportService::lowStockCount(int threshold)
{
    (void)threshold;
    return 0;
}

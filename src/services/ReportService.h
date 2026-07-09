#pragma once
#include <QString>
#include <QDate>
#include <QVector>







class ReportService {
public:
    struct RevenuePoint {
        QString label;
        double revenue = 0;
        int orderCount = 0;
    };

    struct TopProduct {
        int productId = 0;
        QString name;
        int totalSold = 0;
        double totalRevenue = 0;
    };


    QVector<RevenuePoint> revenueByDay(const QDate& from, const QDate& to);


    QVector<RevenuePoint> revenueByMonth(int year);


    QVector<TopProduct> topSellingProducts(int limit = 10);


    double totalRevenueToday();
    int totalOrdersToday();
    int lowStockCount(int threshold = 5);
};

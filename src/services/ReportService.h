#pragma once
#include <QString>
#include <QDate>
#include <QVector>

/*
 * ReportService — thống kê / báo cáo (yêu cầu dashboard trong đề, mục 3.5).
 * NGƯỜI PHỤ TRÁCH: Member 5
 * Gợi ý: dùng SQL GROUP BY trực tiếp cho nhanh, ví dụ:
 *   SELECT DATE(created_at) d, SUM(total) FROM orders GROUP BY d
 */
class ReportService {
public:
    struct RevenuePoint {
        QString label;   // "2026-07-08" hoặc "2026-07"
        double revenue = 0;
        int orderCount = 0;
    };

    struct TopProduct {
        int productId = 0;
        QString name;
        int totalSold = 0;
        double totalRevenue = 0;
    };

    // Doanh thu theo ngày trong khoảng [from, to]
    QVector<RevenuePoint> revenueByDay(const QDate& from, const QDate& to);

    // Doanh thu theo tháng của 1 năm
    QVector<RevenuePoint> revenueByMonth(int year);

    // Top N sản phẩm bán chạy
    QVector<TopProduct> topSellingProducts(int limit = 10);

    // Số liệu tổng quan cho các thẻ trên dashboard
    double totalRevenueToday();
    int totalOrdersToday();
    int lowStockCount(int threshold = 5);
};

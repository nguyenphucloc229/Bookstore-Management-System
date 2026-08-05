#pragma once
#include <QWidget>
#include <QLabel>
#include <QTableWidget>


/*
 * StatisticsPage — màn hình Thống kê / Báo cáo (yêu cầu report/statistics của đề).
 * Phụ trách: Quách Hiền Lương
 *
 * Nội dung hiển thị:
 *  - Ba con số thống kê: doanh thu hôm nay | số đơn hôm nay | SP sắp hết hàng.
 *  - Bảng doanh thu theo ngày (mặc định 7 ngày gần nhất).
 *  - Bảng top sản phẩm bán chạy.
 */
class StatisticsPage : public QWidget {
    Q_OBJECT

public:
    explicit StatisticsPage(QWidget* parent = nullptr);

    // Nạp lại số liệu thống kê — MainWindow gọi mỗi khi chuyển sang tab này
    void refreshData();

private:
    void setupUi();
    void reloadStats();

    QLabel *revenueLabel;
    QLabel *ordersLabel;
    QLabel *stockLabel;

    QTableWidget *revenueTable;
    QTableWidget *topTable;
};
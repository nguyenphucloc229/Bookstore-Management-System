#pragma once
#include <QWidget>

/*
 * StatisticsPage — màn hình Thống kê / Báo cáo (yêu cầu report/statistics của đề).
 * NGƯỜI PHỤ TRÁCH: Lương (Member 5)
 *
 * Yêu cầu UI:
 *  - Vài con số thống kê: tổng doanh thu | số đơn | SP sắp hết hàng.
 *  - Chọn khoảng ngày (QDateEdit from/to) -> bảng doanh thu theo ngày.
 *  - Bảng top sản phẩm bán chạy.
 */
class StatisticsPage : public QWidget {
    Q_OBJECT

public:
    explicit StatisticsPage(QWidget* parent = nullptr);

private:
    void setupUi();
    void reloadStats();
};

#pragma once
#include <QWidget>
#include <QLabel>
#include <QTableWidget>


// Phụ trách: Quách Hiền Lương
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
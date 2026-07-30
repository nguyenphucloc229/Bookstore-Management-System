#include "StatisticsPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>

StatisticsPage::StatisticsPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
}

void StatisticsPage::setupUi()
{
    auto *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("<h2>Bảng điều khiển thống kê</h2>");
    title->setAlignment(Qt::AlignCenter);

    QLabel *revenue = new QLabel("Doanh thu hôm nay: 0 VND");
    QLabel *orders = new QLabel("Đơn hàng hôm nay: 0");
    QLabel *stock = new QLabel("Sản phẩm sắp hết hàng: 0");

    layout->addWidget(title);
    layout->addWidget(revenue);
    layout->addWidget(orders);
    layout->addWidget(stock);

    QLabel *revenueTitle = new QLabel("<b>Doanh thu theo ngày</b>");
    layout->addWidget(revenueTitle);

    QTableWidget *revenueTable = new QTableWidget(0,3,this);
    revenueTable->setHorizontalHeaderLabels(
        {"Ngày","Doanh thu","Đơn hàng"});
    revenueTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(revenueTable);

    QLabel *topTitle = new QLabel("<b>Sản phẩm bán chạy</b>");
    layout->addWidget(topTitle);

    QTableWidget *topTable = new QTableWidget(0,3,this);
    topTable->setHorizontalHeaderLabels(
        {"Sản phẩm","Đã bán","Doanh thu"});
    topTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(topTable);
}

void StatisticsPage::reloadStats()
{
    // TODO(Member 5)
}

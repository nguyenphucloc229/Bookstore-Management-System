#include "StatisticsPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include "ReportService.h"

StatisticsPage::StatisticsPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    reloadStats();
}
void StatisticsPage::setupUi()
{
    auto *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("<h2>Statistics Dashboard</h2>");
    title->setAlignment(Qt::AlignCenter);

    revenueLabel = new QLabel("Today's Revenue: 0 VND");
    ordersLabel = new QLabel("Today's Orders: 0");
    stockLabel = new QLabel("Low Stock Products: 0");
    layout->addWidget(title);
    layout->addWidget(revenueLabel);
    layout->addWidget(ordersLabel);
    layout->addWidget(stockLabel);

    QLabel *revenueTitle = new QLabel("<b>Revenue By Day</b>");
    layout->addWidget(revenueTitle);

    revenueTable = new QTableWidget(0,3,this);
    revenueTable->setHorizontalHeaderLabels(
        {"Date","Revenue","Orders"});
    revenueTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(revenueTable);

    QLabel *topTitle = new QLabel("<b>Top Selling Products</b>");
    layout->addWidget(topTitle);

    topTable = new QTableWidget(0,3,this);
    topTable->setHorizontalHeaderLabels(
        {"Product","Sold","Revenue"});
    topTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(topTable);
}

    void StatisticsPage::reloadStats()
{
    ReportService report;

    revenueLabel->setText(
        QString("Today's Revenue: %1")
        .arg(report.totalRevenueToday()));

    ordersLabel->setText(
        QString("Today's Orders: %1")
        .arg(report.totalOrdersToday()));

    stockLabel->setText(
        QString("Low Stock Products: %1")
        .arg(report.lowStockCount()));

    revenueTable->setRowCount(0);

    auto revenue = report.revenueByDay(
        QDate::currentDate().addDays(-7),
        QDate::currentDate());

    for (const auto &r : revenue)
    {
        int row = revenueTable->rowCount();
        revenueTable->insertRow(row);

        revenueTable->setItem(row, 0, new QTableWidgetItem(r.label));
        revenueTable->setItem(row, 1, new QTableWidgetItem(QString::number(r.revenue)));
        revenueTable->setItem(row, 2, new QTableWidgetItem(QString::number(r.orderCount)));
    }

    topTable->setRowCount(0);

    auto top = report.topSellingProducts();

    for (const auto &p : top)
    {
        int row = topTable->rowCount();
        topTable->insertRow(row);

        topTable->setItem(row, 0, new QTableWidgetItem(p.name));
        topTable->setItem(row, 1, new QTableWidgetItem(QString::number(p.totalSold)));
        topTable->setItem(row, 2, new QTableWidgetItem(QString::number(p.totalRevenue)));
    }
}

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

    QLabel *title = new QLabel("<h2>Statistics Dashboard</h2>");
    title->setAlignment(Qt::AlignCenter);

    QLabel *revenue = new QLabel("Today's Revenue: 0 VND");
    QLabel *orders = new QLabel("Today's Orders: 0");
    QLabel *stock = new QLabel("Low Stock Products: 0");

    layout->addWidget(title);
    layout->addWidget(revenue);
    layout->addWidget(orders);
    layout->addWidget(stock);

    QLabel *revenueTitle = new QLabel("<b>Revenue by Day</b>");
    layout->addWidget(revenueTitle);

    QTableWidget *revenueTable = new QTableWidget(0,3,this);
    revenueTable->setHorizontalHeaderLabels(
        {"Date","Revenue","Orders"});
    revenueTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(revenueTable);

    QLabel *topTitle = new QLabel("<b>Top-Selling Products</b>");
    layout->addWidget(topTitle);

    QTableWidget *topTable = new QTableWidget(0,3,this);
    topTable->setHorizontalHeaderLabels(
        {"Product","Sold","Revenue"});
    topTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(topTable);
}

void StatisticsPage::reloadStats()
{
    // TODO(Member 5)
}

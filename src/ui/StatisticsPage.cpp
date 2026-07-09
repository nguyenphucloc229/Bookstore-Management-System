#include "StatisticsPage.h"
#include <QVBoxLayout>
#include <QLabel>

StatisticsPage::StatisticsPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
}

void StatisticsPage::setupUi()
{

    auto* layout = new QVBoxLayout(this);
    auto* placeholder = new QLabel(
        "Thống kê / Báo cáo", this);
    placeholder->setAlignment(Qt::AlignCenter);
    layout->addWidget(placeholder);
}

void StatisticsPage::reloadStats()
{

}

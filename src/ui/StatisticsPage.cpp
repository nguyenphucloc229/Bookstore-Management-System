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
    // TODO(Member 5 - Lương): thay placeholder bằng UI thật (xem mô tả trong StatisticsPage.h)
    auto* layout = new QVBoxLayout(this);
    auto* placeholder = new QLabel(
        "TODO — Lương (Member 5): Thống kê / Báo cáo", this);
    placeholder->setAlignment(Qt::AlignCenter);
    layout->addWidget(placeholder);
}

void StatisticsPage::reloadStats()
{
    // TODO(Member 5)
}

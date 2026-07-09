#include "CustomerPage.h"
#include <QVBoxLayout>
#include <QLabel>

CustomerPage::CustomerPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
}

void CustomerPage::setupUi()
{
    // TODO(Member 3): thay placeholder bằng UI thật (xem mô tả trong CustomerPage.h)
    auto* layout = new QVBoxLayout(this);
    auto* placeholder = new QLabel(
        "TODO — Member 3: Module Quản lý Khách hàng", this);
    placeholder->setAlignment(Qt::AlignCenter);
    layout->addWidget(placeholder);
}

void CustomerPage::reloadTable()
{
    // TODO(Member 3)
}

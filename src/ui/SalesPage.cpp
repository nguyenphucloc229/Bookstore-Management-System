#include "SalesPage.h"
#include <QVBoxLayout>
#include <QLabel>

SalesPage::SalesPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
}

void SalesPage::setupUi()
{
    // TODO(Member 4): thay placeholder bằng UI thật (xem mô tả trong SalesPage.h)
    auto* layout = new QVBoxLayout(this);
    auto* placeholder = new QLabel(
        "TODO — Member 4: Module Bán hàng (POS)\n"
        "(giỏ hàng + giảm giá + thanh toán + hoá đơn)", this);
    placeholder->setAlignment(Qt::AlignCenter);
    layout->addWidget(placeholder);
}

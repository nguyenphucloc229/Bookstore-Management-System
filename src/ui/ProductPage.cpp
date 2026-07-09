#include "ProductPage.h"
#include <QVBoxLayout>
#include <QLabel>

ProductPage::ProductPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
}

void ProductPage::setupUi()
{
    // TODO(Member 2): thay placeholder bằng UI thật (xem mô tả trong ProductPage.h)
    auto* layout = new QVBoxLayout(this);
    auto* placeholder = new QLabel(
        "TODO — Member 2: Module Quản lý Sản phẩm\n"
        "(bảng + tìm kiếm/lọc + thêm/sửa/xoá + cảnh báo tồn kho)", this);
    placeholder->setAlignment(Qt::AlignCenter);
    layout->addWidget(placeholder);
}

void ProductPage::reloadTable()
{
    // TODO(Member 2)
}

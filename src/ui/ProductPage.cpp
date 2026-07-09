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

    auto* layout = new QVBoxLayout(this);
    auto* placeholder = new QLabel(
        "Quản lý sản phẩm", this);
    placeholder->setAlignment(Qt::AlignCenter);
    layout->addWidget(placeholder);
}

void ProductPage::reloadTable()
{

}

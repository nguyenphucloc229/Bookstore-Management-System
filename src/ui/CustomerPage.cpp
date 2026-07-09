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

    auto* layout = new QVBoxLayout(this);
    auto* placeholder = new QLabel(
        "Quản lý Khách hàng", this);
    placeholder->setAlignment(Qt::AlignCenter);
    layout->addWidget(placeholder);
}

void CustomerPage::reloadTable()
{

}

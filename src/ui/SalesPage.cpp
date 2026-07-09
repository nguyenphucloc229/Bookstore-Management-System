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

    auto* layout = new QVBoxLayout(this);
    auto* placeholder = new QLabel(
        "Bán hàng", this);
    placeholder->setAlignment(Qt::AlignCenter);
    layout->addWidget(placeholder);
}

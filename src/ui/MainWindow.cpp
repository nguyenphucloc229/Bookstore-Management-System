#include "MainWindow.h"
#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include "ui/StatisticsPage.h"
#include "ui/ProductPage.h"
#include "ui/CustomerPage.h"
#include "ui/SalesPage.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Bookstore Management System");
    resize(1150, 720);

    auto* central = new QWidget(this);
    auto* layout = new QHBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_nav = new QListWidget(central);
    m_nav->setFixedWidth(200);

    m_pages = new QStackedWidget(central);

    layout->addWidget(m_nav);
    layout->addWidget(m_pages, 1);
    setCentralWidget(central);

    addPage("Bán hàng", new SalesPage(this));
    addPage("Sản phẩm", new ProductPage(this));
    addPage("Khách hàng", new CustomerPage(this));
    addPage("Thống kê", new StatisticsPage(this));

    connect(m_nav, &QListWidget::currentRowChanged,
            m_pages, &QStackedWidget::setCurrentIndex);
    m_nav->setCurrentRow(0);
}

void MainWindow::addPage(const QString& title, QWidget* page)
{
    m_nav->addItem(title);
    m_pages->addWidget(page);
}

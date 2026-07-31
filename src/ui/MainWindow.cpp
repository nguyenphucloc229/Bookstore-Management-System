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

    m_salesPage = new SalesPage(this);
    m_productPage = new ProductPage(this);
    m_customerPage = new CustomerPage(this);
    m_statisticsPage = new StatisticsPage(this);

    addPage("Sales", m_salesPage);
    addPage("Products", m_productPage);
    addPage("Customers", m_customerPage);
    addPage("Statistics", m_statisticsPage);

    connect(m_nav, &QListWidget::currentRowChanged,
            this, &MainWindow::onPageChanged);
    m_nav->setCurrentRow(0);
}

void MainWindow::onPageChanged(int index)
{
    m_pages->setCurrentIndex(index);

    // Mỗi trang tự nạp lại dữ liệu từ DB khi được mở, nhờ vậy thay đổi ở tab này
    // (thêm sản phẩm, bán hàng...) hiện ngay ở tab khác mà không cần khởi động lại.
    QWidget* current = m_pages->currentWidget();

    if (current == m_salesPage) {
        m_salesPage->refreshData();
    } else if (current == m_productPage) {
        m_productPage->refreshData();
    } else if (current == m_customerPage) {
        m_customerPage->refreshData();
    } else if (current == m_statisticsPage) {
        m_statisticsPage->refreshData();
    }
}

void MainWindow::addPage(const QString& title, QWidget* page)
{
    m_nav->addItem(title);
    m_pages->addWidget(page);
}

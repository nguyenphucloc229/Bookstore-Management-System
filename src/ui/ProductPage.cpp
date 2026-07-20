#include "ProductPage.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>

ProductPage::ProductPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
    reloadTable();
}

void ProductPage::setupUi()
{
    auto* layout = new QVBoxLayout(this);

    // Initialize table widget with 5 columns: ID, Loại, Tên, Giá, Tồn kho
    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels({"ID", "Loại", "Tên", "Giá", "Tồn kho"});
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout->addWidget(m_tableWidget);
}

void ProductPage::reloadTable()
{
    if (!m_tableWidget) return;

    // Fetch all products from ProductRepository
    auto products = m_repository.getAll();
    m_tableWidget->setRowCount(0);

    for (const auto& product : products) {
        if (!product) continue;

        int row = m_tableWidget->rowCount();
        m_tableWidget->insertRow(row);

        m_tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(product->id())));
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(product->getType()));
        m_tableWidget->setItem(row, 2, new QTableWidgetItem(product->name()));
        m_tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(product->price(), 'f', 2) + " VNĐ"));
        m_tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(product->stockQty())));
    }
}
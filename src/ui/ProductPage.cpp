#include "ProductPage.h"
#include "ProductDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QBrush>
#include <QColor>
#include <algorithm>

ProductPage::ProductPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
    reloadTable();
}

void ProductPage::setupUi()
{
    auto* mainLayout = new QVBoxLayout(this);
    auto* topLayout = new QHBoxLayout();

    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("Tìm kiếm theo tên sản phẩm...");

    m_categoryCombo = new QComboBox(this);
    m_categoryCombo->addItems({"Tất cả", "Sách", "Tạp chí", "VPP"});

    m_addButton = new QPushButton("Add", this);
    m_editButton = new QPushButton("Edit", this);
    m_deleteButton = new QPushButton("Delete", this);

    topLayout->addWidget(m_searchEdit, 2);
    topLayout->addWidget(m_categoryCombo, 1);
    topLayout->addWidget(m_addButton);
    topLayout->addWidget(m_editButton);
    topLayout->addWidget(m_deleteButton);

    mainLayout->addLayout(topLayout);

    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels({"ID", "Loại", "Tên", "Giá", "Tồn kho"});
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addWidget(m_tableWidget);

    connect(m_searchEdit, &QLineEdit::textChanged, this, [this](const QString&){ reloadTable(); });
    connect(m_categoryCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int){ reloadTable(); });
    connect(m_addButton, &QPushButton::clicked, this, &ProductPage::onAddButtonClicked);
    connect(m_editButton, &QPushButton::clicked, this, &ProductPage::onEditButtonClicked);
    connect(m_deleteButton, &QPushButton::clicked, this, &ProductPage::onDeleteButtonClicked);
}

void ProductPage::reloadTable()
{
    if (!m_tableWidget) return;

    QString searchText = m_searchEdit ? m_searchEdit->text().trimmed() : "";
    QString category = m_categoryCombo ? m_categoryCombo->currentText() : "Tất cả";

    auto products = m_repository.getAll();
    m_tableWidget->setRowCount(0);

    for (const auto& product : products) {
        if (!product) continue;

        if (!searchText.isEmpty() && !product->name().contains(searchText, Qt::CaseInsensitive)) continue;
        if (category == "Sách" && product->getType() != "BOOK") continue;
        if (category == "Tạp chí" && product->getType() != "MAGAZINE") continue;
        if (category == "VPP" && product->getType() != "STATIONERY") continue;

        int row = m_tableWidget->rowCount();
        m_tableWidget->insertRow(row);

        auto* idItem = new QTableWidgetItem(QString::number(product->id()));
        auto* typeItem = new QTableWidgetItem(product->getType());
        auto* nameItem = new QTableWidgetItem(product->name());
        auto* priceItem = new QTableWidgetItem(QString::number(product->price(), 'f', 2) + " VNĐ");
        auto* stockItem = new QTableWidgetItem(QString::number(product->stockQty()));

        if (product->isLowStock()) {
            QBrush lowStockBrush(QColor(255, 200, 200));
            idItem->setBackground(lowStockBrush);
            typeItem->setBackground(lowStockBrush);
            nameItem->setBackground(lowStockBrush);
            priceItem->setBackground(lowStockBrush);
            stockItem->setBackground(lowStockBrush);
        }

        m_tableWidget->setItem(row, 0, idItem);
        m_tableWidget->setItem(row, 1, typeItem);
        m_tableWidget->setItem(row, 2, nameItem);
        m_tableWidget->setItem(row, 3, priceItem);
        m_tableWidget->setItem(row, 4, stockItem);
    }
}

void ProductPage::onAddButtonClicked()
{
    ProductDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted && dialog.getProduct()) {
        m_repository.add(*dialog.getProduct());
        reloadTable();
    }
}

void ProductPage::onEditButtonClicked()
{
    int currentRow = m_tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn một sản phẩm để sửa.");
        return;
    }

    int productId = m_tableWidget->item(currentRow, 0)->text().toInt();
    auto products = m_repository.getAll();

    auto it = std::find_if(products.begin(), products.end(),
                           [productId](const auto& p) { return p && p->id() == productId; });

    if (it != products.end()) {
        std::shared_ptr<Product> targetProduct(it->get(), [](Product*){});
        ProductDialog dialog(targetProduct, this);
        if (dialog.exec() == QDialog::Accepted && dialog.getProduct()) {
            m_repository.update(*dialog.getProduct());
            reloadTable();
        }
    }
}

void ProductPage::onDeleteButtonClicked()
{
    int currentRow = m_tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn một sản phẩm để xoá.");
        return;
    }

    int productId = m_tableWidget->item(currentRow, 0)->text().toInt();
    if (QMessageBox::question(this, "Xác nhận xoá", QString("Bạn có chắc chắn muốn xoá sản phẩm ID %1?").arg(productId),
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        m_repository.remove(productId);
        reloadTable();
    }
}
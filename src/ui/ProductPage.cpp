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
    m_categoryCombo->addItem("Tất cả", "ALL");
    m_categoryCombo->addItem("Sách", "BOOK");
    m_categoryCombo->addItem("Tạp chí", "MAGAZINE");
    m_categoryCombo->addItem("Văn phòng phẩm", "STATIONERY");

    m_addButton = new QPushButton("Thêm", this);
    m_editButton = new QPushButton("Sửa", this);
    m_deleteButton = new QPushButton("Xóa", this);

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
    QString category = m_categoryCombo ? m_categoryCombo->currentData().toString() : "ALL";

    auto products = m_repository.getAll();
    m_tableWidget->setRowCount(0);

    for (const auto& product : products) {
        if (!product) continue;

        if (!searchText.isEmpty() && !product->name().contains(searchText, Qt::CaseInsensitive)) continue;
        if (category == "BOOK" && product->getType() != "BOOK") continue;
        if (category == "MAGAZINE" && product->getType() != "MAGAZINE") continue;
        if (category == "STATIONERY" && product->getType() != "STATIONERY") continue;

        int row = m_tableWidget->rowCount();
        m_tableWidget->insertRow(row);

        auto* idItem = new QTableWidgetItem(QString::number(product->id()));
        QString typeLabel = product->getType() == "BOOK" ? "Sách"
                            : product->getType() == "MAGAZINE" ? "Tạp chí"
                            : "Văn phòng phẩm";
        auto* typeItem = new QTableWidgetItem(typeLabel);
        auto* nameItem = new QTableWidgetItem(product->name());
        auto* priceItem = new QTableWidgetItem(QString::number(product->price(), 'f', 2) + " VND");
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
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn một sản phẩm để xóa.");
        return;
    }

    int productId = m_tableWidget->item(currentRow, 0)->text().toInt();
    if (QMessageBox::question(this, "Xác nhận xóa", QString("Bạn có chắc chắn muốn xóa sản phẩm ID %1?").arg(productId),
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        m_repository.remove(productId);
        reloadTable();
    }
}
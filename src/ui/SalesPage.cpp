#include "SalesPage.h"
#include "repositories/ProductRepository.h"
#include "models/Book.h"

#include <QTableWidgetItem>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QDebug>
SalesPage::SalesPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
}

void SalesPage::setupUi()
{
    auto* mainLayout = new QVBoxLayout(this);

    auto* titleLabel = new QLabel("BÁN HÀNG (POS)", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    mainLayout->addWidget(titleLabel);

    auto* contentLayout = new QHBoxLayout();

    // =========================================================
    // BÊN TRÁI: TÌM KIẾM VÀ CHỌN SẢN PHẨM
    // =========================================================
    auto* productGroup = new QGroupBox("Danh sách sản phẩm", this);
    auto* productLayout = new QVBoxLayout(productGroup);

    auto* searchLayout = new QHBoxLayout();

    searchEdit = new QLineEdit(productGroup);
    searchEdit->setPlaceholderText("Nhập tên sách hoặc mã sản phẩm...");

    searchButton = new QPushButton("Tìm kiếm", productGroup);

    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);

    productLayout->addLayout(searchLayout);

    productTable = new QTableWidget(productGroup);
    productTable->setColumnCount(5);
    productTable->setHorizontalHeaderLabels({
        "Mã",
        "Tên sản phẩm",
        "Đơn giá",
        "Tồn kho",
        "Tác giả"
    });

    productTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    productTable->setSelectionMode(QAbstractItemView::SingleSelection);
    productTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    productTable->horizontalHeader()->setStretchLastSection(true);
    productTable->horizontalHeader()->setSectionResizeMode(
        1,
        QHeaderView::Stretch
        );

    productLayout->addWidget(productTable);

    auto* addLayout = new QHBoxLayout();

    auto* quantityLabel = new QLabel("Số lượng:", productGroup);

    quantitySpinBox = new QSpinBox(productGroup);
    quantitySpinBox->setRange(1, 999);
    quantitySpinBox->setValue(1);

    addToCartButton = new QPushButton("Thêm vào giỏ", productGroup);

    addLayout->addWidget(quantityLabel);
    addLayout->addWidget(quantitySpinBox);
    addLayout->addStretch();
    addLayout->addWidget(addToCartButton);

    productLayout->addLayout(addLayout);

    // =========================================================
    // BÊN PHẢI: GIỎ HÀNG VÀ THANH TOÁN
    // =========================================================
    auto* cartGroup = new QGroupBox("Giỏ hàng", this);
    auto* cartLayout = new QVBoxLayout(cartGroup);

    auto* customerLayout = new QHBoxLayout();

    auto* customerLabel = new QLabel("Khách hàng:", cartGroup);

    customerComboBox = new QComboBox(cartGroup);
    customerComboBox->addItem("Khách vãng lai", 0);

    customerLayout->addWidget(customerLabel);
    customerLayout->addWidget(customerComboBox);

    cartLayout->addLayout(customerLayout);

    cartTable = new QTableWidget(cartGroup);
    cartTable->setColumnCount(5);
    cartTable->setHorizontalHeaderLabels({
        "Mã",
        "Sản phẩm",
        "Đơn giá",
        "Số lượng",
        "Thành tiền"
    });

    cartTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    cartTable->setSelectionMode(QAbstractItemView::SingleSelection);
    cartTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto *header = cartTable->horizontalHeader();

    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // Mã
    header->setSectionResizeMode(1, QHeaderView::Stretch);          // Sản phẩm
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Đơn giá
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Số lượng
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents); // Thành tiền


    cartLayout->addWidget(cartTable);

    auto* cartButtonLayout = new QHBoxLayout();

    removeItemButton = new QPushButton("Xóa sản phẩm", cartGroup);
    clearCartButton = new QPushButton("Xóa giỏ hàng", cartGroup);

    cartButtonLayout->addWidget(removeItemButton);
    cartButtonLayout->addWidget(clearCartButton);
    cartButtonLayout->addStretch();

    cartLayout->addLayout(cartButtonLayout);

    totalLabel = new QLabel("TỔNG TIỀN: 0.00", cartGroup);

    QFont totalFont = totalLabel->font();
    totalFont.setPointSize(14);
    totalFont.setBold(true);
    totalLabel->setFont(totalFont);
    totalLabel->setAlignment(Qt::AlignRight);

    cartLayout->addWidget(totalLabel);

    checkoutButton = new QPushButton("THANH TOÁN", cartGroup);
    checkoutButton->setMinimumHeight(45);

    QFont checkoutFont = checkoutButton->font();
    checkoutFont.setPointSize(12);
    checkoutFont.setBold(true);
    checkoutButton->setFont(checkoutFont);

    cartLayout->addWidget(checkoutButton);

    // Hai cột trái/phải
    contentLayout->addWidget(productGroup, 1);
    contentLayout->addWidget(cartGroup, 1);

    mainLayout->addLayout(contentLayout);
    connect(searchButton, &QPushButton::clicked,
            this, &SalesPage::loadProducts);

    connect(searchEdit, &QLineEdit::returnPressed,
            this, &SalesPage::loadProducts);

    // Hiển thị toàn bộ sản phẩm ngay khi mở trang
    loadProducts();
}
void SalesPage::loadProducts()
{
    qDebug() << "loadProducts() called";

    const QString keyword = searchEdit->text().trimmed();

    ProductRepository productRepo;
    auto products = keyword.isEmpty()
                        ? productRepo.getAll()
                        : productRepo.search(keyword);

    qDebug() << "Products found:" << products.size();

    productTable->setRowCount(0);


    for (const auto& product : products) {
        if (!product) {
            continue;
        }

        const int row = productTable->rowCount();
        productTable->insertRow(row);

        QString author;

        if (const auto* book = dynamic_cast<const Book*>(product.get())) {
            author = book->author();
        }

        productTable->setItem(
            row,
            0,
            new QTableWidgetItem(QString::number(product->id()))
            );

        productTable->setItem(
            row,
            1,
            new QTableWidgetItem(product->name())
            );

        productTable->setItem(
            row,
            2,
            new QTableWidgetItem(
                QString::number(product->price(), 'f', 2)
                )
            );

        productTable->setItem(
            row,
            3,
            new QTableWidgetItem(
                QString::number(product->stockQty())
                )
            );

        productTable->setItem(
            row,
            4,
            new QTableWidgetItem(author)
            );
    }
}
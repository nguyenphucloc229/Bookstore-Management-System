#include "SalesPage.h"

#include "repositories/ProductRepository.h"
#include "repositories/CustomerRepository.h"
#include "models/Book.h"
#include "models/Order.h"
#include "services/SalesService.h"

#include <QComboBox>
#include <QDateTime>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
SalesPage::SalesPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
}

void SalesPage::setupUi()
{
    auto* mainLayout = new QVBoxLayout(this);

    auto* titleLabel = new QLabel("SALES (POS)", this);
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
    auto* productGroup = new QGroupBox("Product List", this);
    auto* productLayout = new QVBoxLayout(productGroup);

    auto* searchLayout = new QHBoxLayout();

    searchEdit = new QLineEdit(productGroup);
    searchEdit->setPlaceholderText("Enter a product name or ID...");

    searchButton = new QPushButton("Search", productGroup);

    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);

    productLayout->addLayout(searchLayout);

    productTable = new QTableWidget(productGroup);
    productTable->setColumnCount(5);
    productTable->setHorizontalHeaderLabels({
        "ID",
        "Product Name",
        "Unit Price",
        "Stock",
        "Author"
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

    auto* quantityLabel = new QLabel("Quantity:", productGroup);

    quantitySpinBox = new QSpinBox(productGroup);
    quantitySpinBox->setRange(1, 999);
    quantitySpinBox->setValue(1);

    addToCartButton = new QPushButton("Add to Cart", productGroup);

    addLayout->addWidget(quantityLabel);
    addLayout->addWidget(quantitySpinBox);
    addLayout->addStretch();
    addLayout->addWidget(addToCartButton);

    productLayout->addLayout(addLayout);

    // =========================================================
    // BÊN PHẢI: GIỎ HÀNG VÀ THANH TOÁN
    // =========================================================
    auto* cartGroup = new QGroupBox("Cart", this);
    auto* cartLayout = new QVBoxLayout(cartGroup);

    auto* customerLayout = new QHBoxLayout();

    auto* customerLabel = new QLabel("Customer:", cartGroup);

    customerComboBox = new QComboBox(cartGroup);
    reloadCustomers();

    customerLayout->addWidget(customerLabel);
    customerLayout->addWidget(customerComboBox);

    cartLayout->addLayout(customerLayout);

    cartTable = new QTableWidget(cartGroup);
    cartTable->setColumnCount(5);
    cartTable->setHorizontalHeaderLabels({
        "ID",
        "Product",
        "Unit Price",
        "Quantity",
        "Total"
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

    removeItemButton = new QPushButton("Remove Item", cartGroup);
    clearCartButton = new QPushButton("Clear Cart", cartGroup);

    cartButtonLayout->addWidget(removeItemButton);
    cartButtonLayout->addWidget(clearCartButton);
    cartButtonLayout->addStretch();

    cartLayout->addLayout(cartButtonLayout);

    totalLabel = new QLabel("TOTAL: 0.00", cartGroup);

    QFont totalFont = totalLabel->font();
    totalFont.setPointSize(14);
    totalFont.setBold(true);
    totalLabel->setFont(totalFont);
    totalLabel->setAlignment(Qt::AlignRight);

    cartLayout->addWidget(totalLabel);

    checkoutButton = new QPushButton("CHECKOUT", cartGroup);
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
    connect(addToCartButton, &QPushButton::clicked,
            this, &SalesPage::addSelectedProductToCart);

    connect(productTable, &QTableWidget::cellDoubleClicked,
            this, [this](int, int) {
                addSelectedProductToCart();
            });

    connect(removeItemButton, &QPushButton::clicked,
            this, &SalesPage::removeSelectedCartItem);

    connect(clearCartButton, &QPushButton::clicked,
            this, &SalesPage::clearCart);
    connect(checkoutButton, &QPushButton::clicked,
            this, &SalesPage::checkoutOrder);
    // Hiển thị toàn bộ sản phẩm ngay khi mở trang
    loadProducts();
}
void SalesPage::reloadCustomers()
{
    // Giữ lại khách đang chọn để không bị nhảy về "Walk-in" sau khi nạp lại
    const int currentId = customerComboBox->currentData().toInt();

    customerComboBox->clear();
    customerComboBox->addItem("Walk-in Customer", 0);

    // Nạp khách hàng thật vào combo (data của mỗi item = id khách)
    CustomerRepository customerRepo;
    for (const auto& customer : customerRepo.getAll()) {
        if (customer) {
            customerComboBox->addItem(customer->name(), customer->id());
        }
    }

    const int index = customerComboBox->findData(currentId);
    if (index >= 0) {
        customerComboBox->setCurrentIndex(index);
    }
}

void SalesPage::refreshData()
{
    loadProducts();
    reloadCustomers();
}

void SalesPage::loadProducts()
{
    const QString keyword = searchEdit->text().trimmed();

    ProductRepository productRepo;
    auto products = keyword.isEmpty()
                        ? productRepo.getAll()
                        : productRepo.search(keyword);

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
void SalesPage::addSelectedProductToCart()
{
    const int productRow = productTable->currentRow();

    if (productRow < 0) {
        QMessageBox::warning(
            this,
            "No Product Selected",
            "Please select a product."
            );
        return;
    }

    const int productId =
        productTable->item(productRow, 0)->text().toInt();

    const QString productName =
        productTable->item(productRow, 1)->text();

    const double unitPrice =
        productTable->item(productRow, 2)->text().toDouble();

    const int stockQty =
        productTable->item(productRow, 3)->text().toInt();

    const int quantity = quantitySpinBox->value();

    if (stockQty <= 0) {
        QMessageBox::warning(
            this,
            "Out of Stock",
            "This product is currently out of stock."
            );
        return;
    }

    if (quantity > stockQty) {
        QMessageBox::warning(
            this,
            "Insufficient Stock",
            QString("Only %1 product(s) left in stock.").arg(stockQty)
            );
        return;
    }

    // Nếu sản phẩm đã có trong giỏ thì cộng số lượng
    for (int row = 0; row < cartTable->rowCount(); ++row) {
        const int cartProductId =
            cartTable->item(row, 0)->text().toInt();

        if (cartProductId == productId) {
            const int oldQuantity =
                cartTable->item(row, 3)->text().toInt();

            const int newQuantity = oldQuantity + quantity;

            if (newQuantity > stockQty) {
                QMessageBox::warning(
                    this,
                    "Insufficient Stock",
                    QString("Total quantity cannot exceed %1.")
                        .arg(stockQty)
                    );
                return;
            }

            // Cập nhật lại cả đơn giá theo giá hiện tại trong kho, nếu không
            // cột Total sẽ tính theo giá mới còn đơn hàng lưu theo giá cũ.
            cartTable->item(row, 2)->setText(
                QString::number(unitPrice, 'f', 2)
                );

            cartTable->item(row, 3)->setText(
                QString::number(newQuantity)
                );

            cartTable->item(row, 4)->setText(
                QString::number(unitPrice * newQuantity, 'f', 2)
                );

            updateTotal();
            return;
        }
    }

    // Sản phẩm chưa có trong giỏ: thêm dòng mới
    const int cartRow = cartTable->rowCount();
    cartTable->insertRow(cartRow);

    cartTable->setItem(
        cartRow,
        0,
        new QTableWidgetItem(QString::number(productId))
        );

    cartTable->setItem(
        cartRow,
        1,
        new QTableWidgetItem(productName)
        );

    cartTable->setItem(
        cartRow,
        2,
        new QTableWidgetItem(QString::number(unitPrice, 'f', 2))
        );

    cartTable->setItem(
        cartRow,
        3,
        new QTableWidgetItem(QString::number(quantity))
        );

    cartTable->setItem(
        cartRow,
        4,
        new QTableWidgetItem(
            QString::number(unitPrice * quantity, 'f', 2)
            )
        );

    updateTotal();
}
void SalesPage::updateTotal()
{
    double total = 0.0;

    for (int row = 0; row < cartTable->rowCount(); ++row) {
        QTableWidgetItem* totalItem = cartTable->item(row, 4);

        if (totalItem) {
            total += totalItem->text().toDouble();
        }
    }

    totalLabel->setText(
        QString("TOTAL: %1")
            .arg(QString::number(total, 'f', 2))
        );
}
void SalesPage::removeSelectedCartItem()
{
    const int row = cartTable->currentRow();

    if (row < 0) {
        QMessageBox::warning(
            this,
            "No Product Selected",
            "Please select an item to remove from the cart."
            );
        return;
    }

    cartTable->removeRow(row);
    updateTotal();
}
void SalesPage::clearCart()
{
    if (cartTable->rowCount() == 0) {
        return;
    }

    const auto answer = QMessageBox::question(
        this,
        "Clear Cart",
        "Are you sure you want to clear the entire cart?"
        );

    if (answer == QMessageBox::Yes) {
        cartTable->setRowCount(0);
        updateTotal();
    }
}
void SalesPage::checkoutOrder()
{
    if (cartTable->rowCount() == 0) {
        QMessageBox::warning(
            this,
            "Empty Cart",
            "Please add at least one product before checkout."
            );
        return;
    }

    const int customerId = customerComboBox->currentData().toInt();

    Order order(
        0,
        customerId,
        QDateTime::currentDateTime()
        );

    for (int row = 0; row < cartTable->rowCount(); ++row) {
        QTableWidgetItem* idItem = cartTable->item(row, 0);
        QTableWidgetItem* nameItem = cartTable->item(row, 1);
        QTableWidgetItem* priceItem = cartTable->item(row, 2);
        QTableWidgetItem* quantityItem = cartTable->item(row, 3);

        if (!idItem || !nameItem || !priceItem || !quantityItem) {
            QMessageBox::critical(
                this,
                "Invalid Data",
                "A product in the cart is missing information."
                );
            return;
        }

        OrderItem item;
        item.productId = idItem->text().toInt();
        item.productName = nameItem->text();
        item.unitPrice = priceItem->text().toDouble();
        item.quantity = quantityItem->text().toInt();

        order.addItem(item);
    }

    SalesService salesService;
    const SalesService::CheckoutResult result =
        salesService.checkout(order);

    if (!result.success) {
        QMessageBox::critical(
            this,
            "Checkout Failed",
            result.errorMessage.isEmpty()
                ? "Unable to complete the order."
                : result.errorMessage
            );
        return;
    }

    // Gán ID vừa lưu để hóa đơn hiển thị đúng thông tin đơn
    order.setId(result.orderId);

    const QString receipt = salesService.buildReceipt(order);

    QMessageBox receiptBox(this);
    receiptBox.setWindowTitle("Receipt");
    receiptBox.setIcon(QMessageBox::Information);
    receiptBox.setText("Payment completed successfully.");
    receiptBox.setDetailedText(receipt);
    receiptBox.setStandardButtons(QMessageBox::Ok);
    receiptBox.exec();

    cartTable->setRowCount(0);
    quantitySpinBox->setValue(1);
    updateTotal();

    // Tải lại bảng sản phẩm để thấy tồn kho vừa bị trừ sau khi thanh toán
    loadProducts();
}
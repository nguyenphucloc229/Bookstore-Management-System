#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;
class QTableWidget;
class QComboBox;
class QLabel;
class QSpinBox;

class SalesPage : public QWidget
{
    Q_OBJECT

public:
    explicit SalesPage(QWidget* parent = nullptr);

private:
    void setupUi();
    void loadProducts();
    void addSelectedProductToCart();
    void removeSelectedCartItem();
    void clearCart();
    void updateTotal();
    void checkoutOrder();
    // Khu vực tìm kiếm sản phẩm
    QLineEdit* searchEdit = nullptr;
    QPushButton* searchButton = nullptr;
    QTableWidget* productTable = nullptr;
    QSpinBox* quantitySpinBox = nullptr;
    QPushButton* addToCartButton = nullptr;

    // Khu vực giỏ hàng
    QTableWidget* cartTable = nullptr;
    QComboBox* customerComboBox = nullptr;
    QLabel* totalLabel = nullptr;
    QPushButton* removeItemButton = nullptr;
    QPushButton* clearCartButton = nullptr;
    QPushButton* checkoutButton = nullptr;
};
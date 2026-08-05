#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;
class QTableWidget;
class QComboBox;
class QLabel;
class QSpinBox;

/*
 * SalesPage — màn hình Bán hàng (POS).
 * Phụ trách: Võ Viết Tân
 *
 * Bố cục hai cột:
 *  - Trái: tìm sản phẩm, bảng kết quả, chọn số lượng, thêm vào giỏ.
 *  - Phải: chọn khách hàng, giỏ hàng, tổng tiền, nút thanh toán.
 * Khi thanh toán, SalesService kiểm tồn kho, lưu đơn, trừ kho, cộng điểm
 * rồi sinh hoá đơn hiển thị cho người dùng.
 */
class SalesPage : public QWidget
{
    Q_OBJECT

public:
    explicit SalesPage(QWidget* parent = nullptr);

    // Nạp lại sản phẩm + danh sách khách hàng — MainWindow gọi khi chuyển sang tab này
    void refreshData();

private:
    void setupUi();
    void loadProducts();
    void reloadCustomers();
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
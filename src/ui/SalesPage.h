#pragma once
#include <QWidget>

/*
 * SalesPage — màn hình Bán hàng (POS) — TRÁI TIM của đồ án.
 * NGƯỜI PHỤ TRÁCH: Member 4
 *
 * Layout gợi ý (2 cột):
 *  - Trái: tìm sản phẩm + bảng kết quả, double-click để thêm vào giỏ.
 *  - Phải: GIỎ HÀNG (bảng item + sửa số lượng + xoá),
 *          combo chọn khách hàng (hoặc "Khách vãng lai"),
 *          hiển thị subtotal / giảm giá / TỔNG,
 *          nút "Thanh toán" -> gọi SalesService::checkout()
 *          -> thành công thì hiện dialog HOÁ ĐƠN (buildReceipt).
 *
 * Validate: giỏ rỗng không cho thanh toán, số lượng vượt tồn kho -> báo lỗi.
 */
class SalesPage : public QWidget {
    Q_OBJECT

public:
    explicit SalesPage(QWidget* parent = nullptr);

private:
    void setupUi();
};

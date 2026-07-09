#pragma once
#include <QWidget>

/*
 * ProductPage — màn hình Quản lý sản phẩm.
 * NGƯỜI PHỤ TRÁCH: Member 2
 *
 * Yêu cầu UI:
 *  - QTableWidget/QTableView hiển thị danh sách (cột: ID, Loại, Tên, Giá, Tồn kho).
 *  - Ô tìm kiếm (QLineEdit) + combo lọc theo loại (Tất cả/Sách/Tạp chí/VPP).
 *  - Nút Thêm / Sửa / Xoá -> mở dialog form (form đổi field theo loại sản phẩm).
 *  - Validate: tên không rỗng, giá > 0, tồn kho >= 0 -> sai thì QMessageBox báo lỗi.
 *  - Dòng nào sắp hết hàng (isLowStock) -> tô màu đỏ/vàng cảnh báo.
 */
class ProductPage : public QWidget {
    Q_OBJECT

public:
    explicit ProductPage(QWidget* parent = nullptr);

private:
    void setupUi();
    void reloadTable();   // đọc từ ProductRepository và đổ vào bảng
};

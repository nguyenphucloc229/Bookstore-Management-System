#pragma once
#include <QWidget>

/*
 * CustomerPage — màn hình Quản lý khách hàng.
 * NGƯỜI PHỤ TRÁCH: Member 3
 *
 * Yêu cầu UI:
 *  - Bảng: ID, Tên, SĐT, Email, Điểm, Hạng (Regular/Silver/Gold).
 *  - Tìm kiếm theo tên hoặc SĐT.
 *  - Thêm / Sửa / Xoá với dialog form + validate (tên không rỗng, SĐT đúng dạng số).
 */
class CustomerPage : public QWidget {
    Q_OBJECT

public:
    explicit CustomerPage(QWidget* parent = nullptr);

private:
    void setupUi();
    void reloadTable();
};

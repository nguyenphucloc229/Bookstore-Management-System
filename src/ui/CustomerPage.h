#pragma once
#include <QTableWidget>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QObject>

/*
 * CustomerPage — màn hình Quản lý khách hàng.
 * Phụ trách: Nguyễn Trịnh Quốc Đạt
 *
 * Nội dung hiển thị:
 *  - Bảng: ID, Tên, SĐT, Email, Điểm, Hạng (Regular/Silver/Gold).
 *  - Tìm kiếm theo tên hoặc SĐT.
 *  - Thêm / Sửa / Xoá qua CustomerDialog, có kiểm tra dữ liệu nhập.
 */
 class CustomerPage : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerPage(QWidget *parent = nullptr);

    // Nạp lại dữ liệu từ DB — MainWindow gọi mỗi khi chuyển sang tab này
    void refreshData();

private slots:
    void reloadTable();

    void onSearchClicked();
    void onAddClicked();
    void onEditClicked();
    void onDeleteClicked();

private:
    void setupUi();

    // Search
    QLineEdit *searchEdit;
    QPushButton *searchButton;

    // Customer table
    QTableWidget *table;

    // Buttons
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
};

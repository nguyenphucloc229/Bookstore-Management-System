#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "../repositories/ProductRepository.h"

/*
 * ProductPage – Giao diện quản lý danh sách sản phẩm
 * Phụ trách: Vũ Bình Nguyên
 */
class ProductPage : public QWidget {
    Q_OBJECT

public:
    explicit ProductPage(QWidget* parent = nullptr);

    // Nạp lại dữ liệu từ DB — MainWindow gọi mỗi khi chuyển sang tab này
    void refreshData();

private:
    void setupUi();
    void reloadTable();

    void onAddButtonClicked();
    void onEditButtonClicked();
    void onDeleteButtonClicked();

    QTableWidget* m_tableWidget{nullptr};
    QLineEdit* m_searchEdit{nullptr};
    QComboBox* m_categoryCombo{nullptr};
    QPushButton* m_addButton{nullptr};
    QPushButton* m_editButton{nullptr};
    QPushButton* m_deleteButton{nullptr};

    ProductRepository m_repository;
};
#pragma once
#include <QWidget>
#include <QTableWidget>
#include "../repositories/ProductRepository.h"

/*
 * ProductPage – màn hình Quản lý sản phẩm.
 * NGƯỜI PHỤ TRÁCH: Member 2 (Vũ Bình Nguyên)
 */
class ProductPage : public QWidget {
    Q_OBJECT

public:
    explicit ProductPage(QWidget* parent = nullptr);

private:
    void setupUi();
    void reloadTable(); // đọc từ ProductRepository và đổ vào bảng

    QTableWidget* m_tableWidget = nullptr;
    ProductRepository m_repository;
};
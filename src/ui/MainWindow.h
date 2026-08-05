#pragma once
#include <QMainWindow>

class QListWidget;
class QStackedWidget;
class SalesPage;
class ProductPage;
class CustomerPage;
class StatisticsPage;

/*
 * MainWindow — khung chính: sidebar điều hướng bên trái + vùng nội dung bên phải.
 * Mỗi module là 1 page trong QStackedWidget (yêu cầu "clear navigation" của đề).
 * Phụ trách: Nguyễn Phúc Lộc
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void addPage(const QString& title, QWidget* page);

    // Đổi trang + nạp lại dữ liệu của trang đó (tránh hiển thị số liệu cũ)
    void onPageChanged(int index);

    QListWidget* m_nav = nullptr;
    QStackedWidget* m_pages = nullptr;

    SalesPage* m_salesPage = nullptr;
    ProductPage* m_productPage = nullptr;
    CustomerPage* m_customerPage = nullptr;
    StatisticsPage* m_statisticsPage = nullptr;
};

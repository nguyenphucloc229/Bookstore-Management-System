#pragma once
#include <QMainWindow>

class QListWidget;
class QStackedWidget;

/*
 * MainWindow — khung chính: sidebar điều hướng bên trái + vùng nội dung bên phải.
 * Mỗi module là 1 page trong QStackedWidget (yêu cầu "clear navigation" của đề).
 * NGƯỜI PHỤ TRÁCH: Member 1 (Lộc)
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void addPage(const QString& title, QWidget* page);

    QListWidget* m_nav = nullptr;
    QStackedWidget* m_pages = nullptr;
};

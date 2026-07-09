#pragma once
#include <QMainWindow>

class QListWidget;
class QStackedWidget;






class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void addPage(const QString& title, QWidget* page);

    QListWidget* m_nav = nullptr;
    QStackedWidget* m_pages = nullptr;
};

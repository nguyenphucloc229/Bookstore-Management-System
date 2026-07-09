#pragma once
#include <QWidget>












class ProductPage : public QWidget {
    Q_OBJECT

public:
    explicit ProductPage(QWidget* parent = nullptr);

private:
    void setupUi();
    void reloadTable();
};

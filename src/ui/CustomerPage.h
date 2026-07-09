#pragma once
#include <QWidget>










class CustomerPage : public QWidget {
    Q_OBJECT

public:
    explicit CustomerPage(QWidget* parent = nullptr);

private:
    void setupUi();
    void reloadTable();
};

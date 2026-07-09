#pragma once
#include <QWidget>















class SalesPage : public QWidget {
    Q_OBJECT

public:
    explicit SalesPage(QWidget* parent = nullptr);

private:
    void setupUi();
};

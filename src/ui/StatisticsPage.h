#pragma once
#include <QWidget>










class StatisticsPage : public QWidget {
    Q_OBJECT

public:
    explicit StatisticsPage(QWidget* parent = nullptr);

private:
    void setupUi();
    void reloadStats();
};

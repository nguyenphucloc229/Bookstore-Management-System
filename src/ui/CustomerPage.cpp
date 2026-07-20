#include "CustomerPage.h"
#include <QVBoxLayout>
#include <QLabel>

CustomerPage::CustomerPage(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
}

void CustomerPage::setupUi()
{
    auto *layout = new QVBoxLayout(this);

    table = new QTableWidget(this);

    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({
        "ID",
        "Name",
        "Phone",
        "Email"
    });

    layout->addWidget(table);

    reloadTable();
}

#include "repositories/CustomerRepository.h"

void CustomerPage::reloadTable()
{
    CustomerRepository repo;
    auto customers = repo.getAll();

    table->setRowCount(customers.size());

    for (int i = 0; i < customers.size(); ++i)
    {
        table->setItem(i, 0,
                       new QTableWidgetItem(QString::number(customers[i]->id())));

        table->setItem(i, 1,
                       new QTableWidgetItem(customers[i]->name()));

        table->setItem(i, 2,
                       new QTableWidgetItem(customers[i]->phone()));

        table->setItem(i, 3,
                       new QTableWidgetItem(customers[i]->email()));
    }

    table->resizeColumnsToContents();
}
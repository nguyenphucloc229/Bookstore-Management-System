#include "CustomerPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

#include "repositories/CustomerRepository.h"
#include "ui/CustomerDialog.h"

void CustomerPage::refreshData()
{
    reloadTable();
}

CustomerPage::CustomerPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    reloadTable();

    connect(searchButton, &QPushButton::clicked,
            this, &CustomerPage::onSearchClicked);

    connect(addButton, &QPushButton::clicked,
            this, &CustomerPage::onAddClicked);

    connect(editButton, &QPushButton::clicked,
            this, &CustomerPage::onEditClicked);

    connect(deleteButton, &QPushButton::clicked,
            this, &CustomerPage::onDeleteClicked);
}

void CustomerPage::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    // Search
    auto *searchLayout = new QHBoxLayout;

    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("Enter name or phone number");

    searchButton = new QPushButton("Search");

    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);

    // Table
    table = new QTableWidget;

    table->setColumnCount(6);

    table->setHorizontalHeaderLabels({
        "ID",
        "Name",
        "Phone",
        "Email",
        "Points",
        "Tier"
    });

    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Buttons
    auto *buttonLayout = new QHBoxLayout;

    addButton = new QPushButton("Add");
    editButton = new QPushButton("Edit");
    deleteButton = new QPushButton("Delete");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);
}

void CustomerPage::reloadTable()
{
    CustomerRepository repo;

    auto customers = repo.getAll();

    table->setRowCount(customers.size());

    for (int i = 0; i < customers.size(); i++)
    {
        table->setItem(i, 0,
                       new QTableWidgetItem(QString::number(customers[i]->id())));

        table->setItem(i, 1,
                       new QTableWidgetItem(customers[i]->name()));

        table->setItem(i, 2,
                       new QTableWidgetItem(customers[i]->phone()));

        table->setItem(i, 3,
                       new QTableWidgetItem(customers[i]->email()));

        // Temporary values until point/rank exist in database
        table->setItem(i, 4,
                       new QTableWidgetItem(QString::number(customers[i]->point())));

        table->setItem(i, 5,
                       new QTableWidgetItem(customers[i]->rank() == "Gold" ? "Gold"
                                            : customers[i]->rank() == "Silver" ? "Silver"
                                            : "Regular"));
    }
}

void CustomerPage::onSearchClicked()
{
    CustomerRepository repo;

    auto customers = repo.search(searchEdit->text());

    table->setRowCount(customers.size());

    for (int i = 0; i < customers.size(); i++)
    {
        table->setItem(i, 0,
                       new QTableWidgetItem(QString::number(customers[i]->id())));

        table->setItem(i, 1,
                       new QTableWidgetItem(customers[i]->name()));

        table->setItem(i, 2,
                       new QTableWidgetItem(customers[i]->phone()));

        table->setItem(i, 3,
                       new QTableWidgetItem(customers[i]->email()));

        table->setItem(i, 4,
                       new QTableWidgetItem(QString::number(customers[i]->point())));

        table->setItem(i, 5,
                       new QTableWidgetItem(customers[i]->rank()));
    }
}

void CustomerPage::onAddClicked()
{
    CustomerDialog dialog(this);
    dialog.setAddMode();

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    Customer customer(
        0,
        dialog.name(),
        dialog.phone(),
        dialog.email(),
        dialog.point(),
        dialog.rank()
        );

    CustomerRepository repo;

    int newId = repo.add(customer);

    if (newId < 0)
    {
        QMessageBox::critical(
            this,
            "Error",
            "Unable to add the customer."
            );
        return;
    }

    reloadTable();

    QMessageBox::information(
        this,
        "Success",
        "Customer added successfully."
        );
}

void CustomerPage::onEditClicked()
{
    int row = table->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(
            this,
            "Notice",
            "Please select a customer to edit."
            );
        return;
    }

    QTableWidgetItem *idItem = table->item(row, 0);

    if (idItem == nullptr)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Unable to read the customer ID."
            );
        return;
    }

    int id = idItem->text().toInt();

    CustomerRepository repo;
    auto customer = repo.findById(id);

    if (!customer)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Customer not found."
            );
        return;
    }

    CustomerDialog dialog(this);
    dialog.setEditMode();

    dialog.setCustomer(
        customer->name(),
        customer->phone(),
        customer->email(),
        customer->point(),
        customer->rank()
        );

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    customer->setName(dialog.name());
    customer->setPhone(dialog.phone());
    customer->setEmail(dialog.email());
    // setPoint() tự cập nhật hạng nên không cần (và không thể) gán hạng trực tiếp
    customer->setPoint(dialog.point());

    if (!repo.update(*customer))
    {
        QMessageBox::critical(
            this,
            "Error",
            "Unable to update the customer."
            );
        return;
    }

    reloadTable();

    QMessageBox::information(
        this,
        "Success",
        "Customer updated successfully."
        );
}

void CustomerPage::onDeleteClicked()
{
    int row = table->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(this,
                             "Notice",
                             "Please select a customer.");
        return;
    }

    int id = table->item(row, 0)->text().toInt();

    CustomerRepository repo;

    if (repo.remove(id))
    {
        reloadTable();
    }
}
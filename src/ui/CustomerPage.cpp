#include "CustomerPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

#include "repositories/CustomerRepository.h"
#include "ui/CustomerDialog.h"

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
    searchEdit->setPlaceholderText("Nhập tên hoặc SĐT");

    searchButton = new QPushButton("Tìm kiếm");

    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);

    // Table
    table = new QTableWidget;

    table->setColumnCount(6);

    table->setHorizontalHeaderLabels({
        "ID",
        "Tên",
        "SĐT",
        "Email",
        "Điểm",
        "Hạng"
    });

    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Buttons
    auto *buttonLayout = new QHBoxLayout;

    addButton = new QPushButton("Thêm");
    editButton = new QPushButton("Sửa");
    deleteButton = new QPushButton("Xóa");

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
                       new QTableWidgetItem(customers[i]->rank()));
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
                       new QTableWidgetItem("0"));

        table->setItem(i, 5,
                       new QTableWidgetItem("Regular"));
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
            "Lỗi",
            "Không thể thêm khách hàng."
            );
        return;
    }

    reloadTable();

    QMessageBox::information(
        this,
        "Thành công",
        "Đã thêm khách hàng."
        );
}

void CustomerPage::onEditClicked()
{
    int row = table->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(
            this,
            "Thông báo",
            "Hãy chọn khách hàng cần sửa."
            );
        return;
    }

    QTableWidgetItem *idItem = table->item(row, 0);

    if (idItem == nullptr)
    {
        QMessageBox::warning(
            this,
            "Lỗi",
            "Không thể đọc ID khách hàng."
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
            "Lỗi",
            "Không tìm thấy khách hàng."
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
    customer->setPoint(dialog.point());
    customer->setRank(dialog.rank());

    if (!repo.update(*customer))
    {
        QMessageBox::critical(
            this,
            "Lỗi",
            "Không thể cập nhật khách hàng."
            );
        return;
    }

    reloadTable();

    QMessageBox::information(
        this,
        "Thành công",
        "Đã cập nhật khách hàng."
        );
}

void CustomerPage::onDeleteClicked()
{
    int row = table->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(this,
                             "Thông báo",
                             "Hãy chọn khách hàng.");
        return;
    }

    int id = table->item(row, 0)->text().toInt();

    CustomerRepository repo;

    if (repo.remove(id))
    {
        reloadTable();
    }
}
#include "ui/CustomerDialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSpinBox>

CustomerDialog::CustomerDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Customer Information");
    setMinimumWidth(350);

    nameEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);

    pointSpinBox = new QSpinBox(this);
    pointSpinBox->setRange(0, 1000000);
    pointSpinBox->setValue(0);

    rankComboBox = new QComboBox(this);
    rankComboBox->addItem("Regular", "Regular");
    rankComboBox->addItem("Silver", "Silver");
    rankComboBox->addItem("Gold", "Gold");

    // Không cho sửa hạng trực tiếp nếu hạng được tính từ điểm.
    rankComboBox->setEnabled(false);

    buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        this
        );

    auto *layout = new QFormLayout(this);

    layout->addRow("Name:", nameEdit);
    layout->addRow("Phone:", phoneEdit);
    layout->addRow("Email:", emailEdit);
    layout->addRow("Points:", pointSpinBox);
    layout->addRow("Tier:", rankComboBox);
    layout->addWidget(buttonBox);

    connect(pointSpinBox,
            &QSpinBox::valueChanged,
            this,
            &CustomerDialog::updateRankFromPoint);

    connect(buttonBox,
            &QDialogButtonBox::accepted,
            this,
            &CustomerDialog::validateAndAccept);

    connect(buttonBox,
            &QDialogButtonBox::rejected,
            this,
            &CustomerDialog::reject);

    updateRankFromPoint(0);
}

void CustomerDialog::setCustomer(const QString &name,
                                 const QString &phone,
                                 const QString &email,
                                 int point,
                                 const QString &rank)
{
    nameEdit->setText(name);
    phoneEdit->setText(phone);
    emailEdit->setText(email);

    pointSpinBox->setValue(point);

    int rankIndex = rankComboBox->findData(rank);

    if (rankIndex >= 0)
    {
        rankComboBox->setCurrentIndex(rankIndex);
    }
    else
    {
        updateRankFromPoint(point);
    }
}

QString CustomerDialog::name() const
{
    return nameEdit->text().trimmed();
}

QString CustomerDialog::phone() const
{
    return phoneEdit->text().trimmed();
}

QString CustomerDialog::email() const
{
    return emailEdit->text().trimmed();
}

int CustomerDialog::point() const
{
    return pointSpinBox->value();
}

QString CustomerDialog::rank() const
{
    return rankComboBox->currentData().toString();
}

void CustomerDialog::setAddMode()
{
    setWindowTitle("Add Customer");

    pointSpinBox->setValue(0);
    rankComboBox->setCurrentIndex(rankComboBox->findData("Regular"));

    pointSpinBox->setEnabled(true);
    // Hạng luôn suy ra từ điểm (updateRankFromPoint), không cho sửa tay
    // để dữ liệu không mâu thuẫn (vd: 0 điểm nhưng hạng Gold).
    rankComboBox->setEnabled(false);
}

void CustomerDialog::setEditMode()
{
    setWindowTitle("Edit Customer");

    pointSpinBox->setEnabled(true);
    rankComboBox->setEnabled(false);   // xem mục setAddMode()
}

void CustomerDialog::updateRankFromPoint(int point)
{
    if (point >= 1000)
    {
        rankComboBox->setCurrentIndex(rankComboBox->findData("Gold"));
    }
    else if (point >= 500)
    {
        rankComboBox->setCurrentIndex(rankComboBox->findData("Silver"));
    }
    else
    {
        rankComboBox->setCurrentIndex(rankComboBox->findData("Regular"));
    }
}

void CustomerDialog::validateAndAccept()
{
    if (name().isEmpty())
    {
        QMessageBox::warning(
            this,
            "Invalid Data",
            "Customer name cannot be empty."
            );

        nameEdit->setFocus();
        return;
    }

    QRegularExpression phoneRegex("^\\d+$");

    if (phone().isEmpty() ||
        !phoneRegex.match(phone()).hasMatch())
    {
        QMessageBox::warning(
            this,
            "Invalid Data",
            "Phone number may contain digits only."
            );

        phoneEdit->setFocus();
        return;
    }

    accept();
}


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
    setWindowTitle("Thông tin khách hàng");
    setMinimumWidth(350);

    nameEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);

    pointSpinBox = new QSpinBox(this);
    pointSpinBox->setRange(0, 1000000);
    pointSpinBox->setValue(0);

    rankComboBox = new QComboBox(this);
    rankComboBox->addItem("Regular");
    rankComboBox->addItem("Silver");
    rankComboBox->addItem("Gold");

    // Không cho sửa hạng trực tiếp nếu hạng được tính từ điểm.
    rankComboBox->setEnabled(false);

    buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        this
        );

    auto *layout = new QFormLayout(this);

    layout->addRow("Tên:", nameEdit);
    layout->addRow("SĐT:", phoneEdit);
    layout->addRow("Email:", emailEdit);
    layout->addRow("Điểm:", pointSpinBox);
    layout->addRow("Hạng:", rankComboBox);
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

    int rankIndex = rankComboBox->findText(rank);

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
    return rankComboBox->currentText();
}

void CustomerDialog::setAddMode()
{
    setWindowTitle("Thêm khách hàng");

    pointSpinBox->setValue(0);
    rankComboBox->setCurrentText("Regular");

    pointSpinBox->setEnabled(true);
    rankComboBox->setEnabled(true);
}

void CustomerDialog::setEditMode()
{
    setWindowTitle("Sửa khách hàng");

    pointSpinBox->setEnabled(true);
    rankComboBox->setEnabled(true);
}

void CustomerDialog::updateRankFromPoint(int point)
{
    if (point >= 1000)
    {
        rankComboBox->setCurrentText("Gold");
    }
    else if (point >= 500)
    {
        rankComboBox->setCurrentText("Silver");
    }
    else
    {
        rankComboBox->setCurrentText("Regular");
    }
}

void CustomerDialog::validateAndAccept()
{
    if (name().isEmpty())
    {
        QMessageBox::warning(
            this,
            "Dữ liệu không hợp lệ",
            "Tên khách hàng không được để trống."
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
            "Dữ liệu không hợp lệ",
            "Số điện thoại chỉ được chứa chữ số."
            );

        phoneEdit->setFocus();
        return;
    }

    accept();
}


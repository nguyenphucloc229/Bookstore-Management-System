#include "ProductDialog.h"
#include "../models/Book.h"
#include "../models/Magazine.h"
#include "../models/Stationery.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>

ProductDialog::ProductDialog(QWidget* parent)
    : QDialog(parent), m_isEditMode(false)
{
    setupUi();
    setWindowTitle("Thêm Sản Phẩm Mới");
}

ProductDialog::ProductDialog(std::shared_ptr<Product> product, QWidget* parent)
    : QDialog(parent), m_product(product), m_isEditMode(true)
{
    setupUi();
    setWindowTitle("Sửa Thông Tin Sản Phẩm");

    if (m_product) {
        m_nameEdit->setText(m_product->name());
        m_priceSpin->setValue(m_product->price());
        m_stockSpin->setValue(m_product->stockQty());

        int index = m_typeCombo->findText(m_product->getType());
        if (index >= 0) m_typeCombo->setCurrentIndex(index);

        if (auto book = std::dynamic_pointer_cast<Book>(m_product)) {
            m_extra1Edit->setText(book->isbn());
            m_extra2Edit->setText(book->author());
            m_extra3Edit->setText(book->publisher());
        } else if (auto mag = std::dynamic_pointer_cast<Magazine>(m_product)) {
            m_extra1Edit->setText(QString::number(mag->issueNumber()));
            m_extra2Edit->setText(mag->publishDate());
        } else if (auto stat = std::dynamic_pointer_cast<Stationery>(m_product)) {
            m_extra1Edit->setText(stat->brand());
            m_extra2Edit->setText(stat->category());
        }
    }
}

void ProductDialog::setupUi()
{
    auto* mainLayout = new QVBoxLayout(this);
    auto* formLayout = new QFormLayout();

    m_typeCombo = new QComboBox(this);
    m_typeCombo->addItems({"Book", "Magazine", "Stationery"});
    if (m_isEditMode) m_typeCombo->setEnabled(false);
    formLayout->addRow("Loại sản phẩm:", m_typeCombo);

    m_nameEdit = new QLineEdit(this);
    formLayout->addRow("Tên sản phẩm:", m_nameEdit);

    m_priceSpin = new QDoubleSpinBox(this);
    m_priceSpin->setRange(0, 1000000000);
    m_priceSpin->setSuffix(" VNĐ");
    formLayout->addRow("Giá bán:", m_priceSpin);

    m_stockSpin = new QSpinBox(this);
    m_stockSpin->setRange(0, 100000);
    formLayout->addRow("Số lượng tồn:", m_stockSpin);

    m_lblExtra1 = new QLabel(this);
    m_extra1Edit = new QLineEdit(this);
    m_lblExtra2 = new QLabel(this);
    m_extra2Edit = new QLineEdit(this);
    m_lblExtra3 = new QLabel(this);
    m_extra3Edit = new QLineEdit(this);

    formLayout->addRow(m_lblExtra1, m_extra1Edit);
    formLayout->addRow(m_lblExtra2, m_extra2Edit);
    formLayout->addRow(m_lblExtra3, m_extra3Edit);

    mainLayout->addLayout(formLayout);

    auto* btnLayout = new QHBoxLayout();
    auto* saveBtn = new QPushButton("Save", this);
    auto* cancelBtn = new QPushButton("Cancel", this);

    btnLayout->addStretch();
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(cancelBtn);
    mainLayout->addLayout(btnLayout);

    connect(m_typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int){
        updateDynamicFields(m_typeCombo->currentText());
    });
    connect(saveBtn, &QPushButton::clicked, this, &ProductDialog::onSaveClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    updateDynamicFields(m_typeCombo->currentText());
}

void ProductDialog::updateDynamicFields(const QString& type)
{
    bool isBook = (type == "Book");
    bool isMag = (type == "Magazine");

    m_lblExtra1->setText(isBook ? "ISBN:" : (isMag ? "Số phát hành:" : "Thương hiệu:"));
    m_lblExtra2->setText(isBook ? "Tác giả:" : (isMag ? "Tháng/Năm:" : "Danh mục VPP:"));
    m_lblExtra3->setText("Nhà xuất bản:");

    m_lblExtra1->setVisible(true);  m_extra1Edit->setVisible(true);
    m_lblExtra2->setVisible(true);  m_extra2Edit->setVisible(true);
    m_lblExtra3->setVisible(isBook); m_extra3Edit->setVisible(isBook);
}

bool ProductDialog::validateInputs()
{
    if (m_nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Lỗi nhập liệu", "Tên sản phẩm không được để trống!");
        return false;
    }
    if (m_priceSpin->value() <= 0) {
        QMessageBox::warning(this, "Lỗi nhập liệu", "Giá sản phẩm phải lớn hơn 0!");
        return false;
    }
    return true;
}

void ProductDialog::onSaveClicked()
{
    if (!validateInputs()) return;

    QString type = m_typeCombo->currentText();
    QString name = m_nameEdit->text().trimmed();
    double price = m_priceSpin->value();
    int stock = m_stockSpin->value();
    int id = (m_isEditMode && m_product) ? m_product->id() : 0;

    if (type == "Book") {
        m_product = std::make_shared<Book>(id, name, price, stock,
                                           m_extra1Edit->text().trimmed(),
                                           m_extra2Edit->text().trimmed(),
                                           m_extra3Edit->text().trimmed(),
                                           "");
    } else if (type == "Magazine") {
        m_product = std::make_shared<Magazine>(id, name, price, stock,
                                               m_extra1Edit->text().toInt(),
                                               m_extra2Edit->text().trimmed());
    } else if (type == "Stationery") {
        m_product = std::make_shared<Stationery>(id, name, price, stock,
                                                 m_extra1Edit->text().trimmed(),
                                                 m_extra2Edit->text().trimmed());
    }

    accept();
}
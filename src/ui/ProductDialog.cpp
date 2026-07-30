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
    setWindowTitle("Add New Product");
}

ProductDialog::ProductDialog(std::shared_ptr<Product> product, QWidget* parent)
    : QDialog(parent), m_product(product), m_isEditMode(true)
{
    setupUi();
    setWindowTitle("Edit Product Information");

    if (m_product) {
        m_nameEdit->setText(m_product->name());
        m_priceSpin->setValue(m_product->price());
        m_stockSpin->setValue(m_product->stockQty());

        int index = m_typeCombo->findData(m_product->getType());
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
    m_typeCombo->addItem("Book", "BOOK");
    m_typeCombo->addItem("Magazine", "MAGAZINE");
    m_typeCombo->addItem("Stationery", "STATIONERY");
    if (m_isEditMode) m_typeCombo->setEnabled(false);
    formLayout->addRow("Product Type:", m_typeCombo);

    m_nameEdit = new QLineEdit(this);
    formLayout->addRow("Product Name:", m_nameEdit);

    m_priceSpin = new QDoubleSpinBox(this);
    m_priceSpin->setRange(0, 1000000000);
    m_priceSpin->setSuffix(" VND");
    formLayout->addRow("Price:", m_priceSpin);

    m_stockSpin = new QSpinBox(this);
    m_stockSpin->setRange(0, 100000);
    formLayout->addRow("Stock Quantity:", m_stockSpin);

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
        updateDynamicFields(m_typeCombo->currentData().toString());
    });
    connect(saveBtn, &QPushButton::clicked, this, &ProductDialog::onSaveClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    updateDynamicFields(m_typeCombo->currentData().toString());
}

void ProductDialog::updateDynamicFields(const QString& type)
{
    bool isBook = (type == "BOOK");
    bool isMag = (type == "MAGAZINE");

    m_lblExtra1->setText(isBook ? "ISBN:" : (isMag ? "Issue Number:" : "Brand:"));
    m_lblExtra2->setText(isBook ? "Author:" : (isMag ? "Month/Year:" : "Stationery Category:"));
    m_lblExtra3->setText("Publisher:");

    m_lblExtra1->setVisible(true);  m_extra1Edit->setVisible(true);
    m_lblExtra2->setVisible(true);  m_extra2Edit->setVisible(true);
    m_lblExtra3->setVisible(isBook); m_extra3Edit->setVisible(isBook);
}

bool ProductDialog::validateInputs()
{
    if (m_nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Product name cannot be empty!");
        return false;
    }
    if (m_priceSpin->value() <= 0) {
        QMessageBox::warning(this, "Input Error", "Product price must be greater than 0!");
        return false;
    }
    return true;
}

void ProductDialog::onSaveClicked()
{
    if (!validateInputs()) return;

    QString type = m_typeCombo->currentData().toString();
    QString name = m_nameEdit->text().trimmed();
    double price = m_priceSpin->value();
    int stock = m_stockSpin->value();
    int id = (m_isEditMode && m_product) ? m_product->id() : 0;

    if (type == "BOOK") {
        m_product = std::make_shared<Book>(id, name, price, stock,
                                           m_extra1Edit->text().trimmed(),
                                           m_extra2Edit->text().trimmed(),
                                           m_extra3Edit->text().trimmed(),
                                           "");
    } else if (type == "MAGAZINE") {
        m_product = std::make_shared<Magazine>(id, name, price, stock,
                                               m_extra1Edit->text().toInt(),
                                               m_extra2Edit->text().trimmed());
    } else if (type == "STATIONERY") {
        m_product = std::make_shared<Stationery>(id, name, price, stock,
                                                 m_extra1Edit->text().trimmed(),
                                                 m_extra2Edit->text().trimmed());
    }

    accept();
}
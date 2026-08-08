#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <memory>
#include "../models/Product.h"

// Phụ trách: Vũ Bình Nguyên
class ProductDialog : public QDialog {
    Q_OBJECT

public:
    explicit ProductDialog(QWidget* parent = nullptr);
    explicit ProductDialog(std::shared_ptr<Product> product, QWidget* parent = nullptr);

    std::shared_ptr<Product> getProduct() const { return m_product; }

private:
    void setupUi();
    void updateDynamicFields(const QString& type);
    bool validateInputs();
    void onSaveClicked();

    QComboBox* m_typeCombo{nullptr};
    QLineEdit* m_nameEdit{nullptr};
    QDoubleSpinBox* m_priceSpin{nullptr};
    QSpinBox* m_stockSpin{nullptr};

    QLineEdit* m_extra1Edit{nullptr};
    QLineEdit* m_extra2Edit{nullptr};
    QLineEdit* m_extra3Edit{nullptr};
    QLineEdit* m_extra4Edit{nullptr};   // Genre (chỉ dùng cho Book)

    QLabel* m_lblExtra1{nullptr};
    QLabel* m_lblExtra2{nullptr};
    QLabel* m_lblExtra3{nullptr};
    QLabel* m_lblExtra4{nullptr};

    std::shared_ptr<Product> m_product{nullptr};
    bool m_isEditMode{false};
};
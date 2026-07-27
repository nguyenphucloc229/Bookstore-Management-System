#pragma once

#include <QDialog>

class QLineEdit;
class QComboBox;
class QSpinBox;
class QDialogButtonBox;

class CustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerDialog(QWidget *parent = nullptr);

    void setAddMode();
    void setEditMode();

    void setCustomer(const QString &name,
                     const QString &phone,
                     const QString &email,
                     int point,
                     const QString &rank);

    QString name() const;
    QString phone() const;
    QString email() const;
    int point() const;
    QString rank() const;

private slots:
    void validateAndAccept();
    void updateRankFromPoint(int point);

private:
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QLineEdit *emailEdit;

    QSpinBox *pointSpinBox;
    QComboBox *rankComboBox;

    QDialogButtonBox *buttonBox;
};
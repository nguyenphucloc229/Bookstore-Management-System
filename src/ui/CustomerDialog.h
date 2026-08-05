#pragma once

#include <QDialog>

class QLineEdit;
class QComboBox;
class QSpinBox;
class QDialogButtonBox;

/*
 * CustomerDialog — hộp thoại Thêm / Sửa khách hàng.
 * Phụ trách: Nguyễn Trịnh Quốc Đạt
 *
 * Ô "Tier" bị khoá: hạng luôn được tính lại từ điểm (updateRankFromPoint)
 * để dữ liệu không mâu thuẫn, ví dụ 0 điểm nhưng hạng Gold.
 */
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
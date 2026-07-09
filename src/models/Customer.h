#pragma once
#include <QString>

/*
 * Customer — khách hàng của cửa hàng.
 * Class đơn giản (không kế thừa), đủ cho scope tối thiểu: lưu thông tin liên hệ.
 */
class Customer {
public:
    Customer(int id, const QString& name, const QString& phone, const QString& email);

    int id() const { return m_id; }
    QString name() const { return m_name; }
    QString phone() const { return m_phone; }
    QString email() const { return m_email; }

    void setId(int id) { m_id = id; }
    void setName(const QString& v) { m_name = v.trimmed(); }
    void setPhone(const QString& v) { m_phone = v.trimmed(); }
    void setEmail(const QString& v) { m_email = v.trimmed(); }

private:
    int m_id;
    QString m_name;
    QString m_phone;
    QString m_email;
};

#pragma once
#include <QString>

/*
 * Customer — khách hàng của cửa hàng.
 * Phụ trách: Nguyễn Trịnh Quốc Đạt
 * Lưu thông tin liên hệ + hệ thống tích luỹ: điểm (point) và hạng thành viên
 * (rank: Regular/Silver/Gold — tự tính từ point qua updateRank()).
 */
class Customer
{
public:
    // Dùng khi đọc đầy đủ dữ liệu từ database
    Customer(int id,
             const QString &name,
             const QString &phone,
             const QString &email,
             int point,
             const QString &rank);

    // Dùng khi tạo khách hàng mới:
    // point = 0, rank = Regular
    Customer(int id,
             const QString &name,
             const QString &phone,
             const QString &email);

    int id() const
    {
        return m_id;
    }

    QString name() const
    {
        return m_name;
    }

    QString phone() const
    {
        return m_phone;
    }

    QString email() const
    {
        return m_email;
    }

    int point() const
    {
        return m_point;
    }

    QString rank() const
    {
        return m_rank;
    }

    void setId(int id)
    {
        m_id = id;
    }

    void setName(const QString &value)
    {
        m_name = value.trimmed();
    }

    void setPhone(const QString &value)
    {
        m_phone = value.trimmed();
    }

    void setEmail(const QString &value)
    {
        m_email = value.trimmed();
    }

    // Đặt điểm, đồng thời tính lại hạng. Không có setRank() công khai:
    // hạng chỉ được suy ra từ điểm nên không thể tạo ra dữ liệu mâu thuẫn
    // (ví dụ 50 điểm nhưng hạng Gold).
    void setPoint(int point);

    // Tính lại hạng dựa trên điểm hiện tại
    void updateRank();

private:
    int m_id;
    QString m_name;
    QString m_phone;
    QString m_email;

    int m_point;
    QString m_rank;
};
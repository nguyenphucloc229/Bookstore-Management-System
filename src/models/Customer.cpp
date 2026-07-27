#include "Customer.h"

// Constructor đầy đủ, dùng khi đọc dữ liệu từ database
Customer::Customer(int id,
                   const QString &name,
                   const QString &phone,
                   const QString &email,
                   int point,
                   const QString &rank)
    : m_id(id),
    m_name(name.trimmed()),
    m_phone(phone.trimmed()),
    m_email(email.trimmed()),
    m_point(point),
    m_rank(rank.trimmed())
{
    // Không chấp nhận điểm âm
    if (m_point < 0)
    {
        m_point = 0;
    }

    // Nếu database chưa có rank thì tự tính
    if (m_rank.isEmpty())
    {
        updateRank();
    }
}

// Constructor cho khách hàng mới
Customer::Customer(int id,
                   const QString &name,
                   const QString &phone,
                   const QString &email)
    : m_id(id),
    m_name(name.trimmed()),
    m_phone(phone.trimmed()),
    m_email(email.trimmed()),
    m_point(0),
    m_rank("Regular")
{
}

void Customer::setPoint(int point)
{
    if (point < 0)
    {
        m_point = 0;
    }
    else
    {
        m_point = point;
    }

    updateRank();
}

void Customer::updateRank()
{
    if (m_point >= 1000)
    {
        m_rank = "Gold";
    }
    else if (m_point >= 500)
    {
        m_rank = "Silver";
    }
    else
    {
        m_rank = "Regular";
    }
}
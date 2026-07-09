#include "Customer.h"

Customer::Customer(int id, const QString& name, const QString& phone, const QString& email)
    : m_id(id), m_name(name.trimmed()), m_phone(phone.trimmed()), m_email(email.trimmed())
{
}

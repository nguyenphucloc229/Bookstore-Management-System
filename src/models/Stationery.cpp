#include "Stationery.h"

Stationery::Stationery(int id, const QString& name, double price, int stockQty,
                       const QString& brand, const QString& category)
    : Product(id, name, price, stockQty),
      m_brand(brand), m_category(category)
{
}

QString Stationery::getDetails() const
{
    return QString("[Stationery] %1 — %2 | Category: %3")
        .arg(name(), m_brand, m_category);
}

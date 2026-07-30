#include "Magazine.h"

Magazine::Magazine(int id, const QString& name, double price, int stockQty,
                   int issueNumber, const QString& publishDate)
    : Product(id, name, price, stockQty),
      m_issueNumber(issueNumber), m_publishDate(publishDate)
{
}

QString Magazine::getDetails() const
{
    return QString("[Magazine] %1 — Issue %2, published %3")
        .arg(name()).arg(m_issueNumber).arg(m_publishDate);
}

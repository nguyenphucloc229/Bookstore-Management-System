#include "Magazine.h"

Magazine::Magazine(int id, const QString& name, double price, int stockQty,
                   int issueNumber, const QString& publishDate)
    : Product(id, name, price, stockQty),
      m_issueNumber(issueNumber), m_publishDate(publishDate)
{
}

QString Magazine::getDetails() const
{
    return QString("[Tạp chí] %1 — Số %2, phát hành %3")
        .arg(name()).arg(m_issueNumber).arg(m_publishDate);
}

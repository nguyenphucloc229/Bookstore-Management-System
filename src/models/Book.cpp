#include "Book.h"

Book::Book(int id, const QString& name, double price, int stockQty,
           const QString& isbn, const QString& author,
           const QString& publisher, const QString& genre)
    : Product(id, name, price, stockQty),
      m_isbn(isbn), m_author(author), m_publisher(publisher), m_genre(genre)
{
}

QString Book::getDetails() const
{
    return QString("[Sách] %1 — %2 (%3) | ISBN: %4 | Thể loại: %5")
        .arg(name(), m_author, m_publisher, m_isbn, m_genre);
}

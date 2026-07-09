#pragma once
#include "Product.h"


class Book : public Product {
public:
    Book(int id, const QString& name, double price, int stockQty,
         const QString& isbn, const QString& author,
         const QString& publisher, const QString& genre);

    QString getType() const override { return "BOOK"; }
    QString getDetails() const override;

    QString isbn() const { return m_isbn; }
    QString author() const { return m_author; }
    QString publisher() const { return m_publisher; }
    QString genre() const { return m_genre; }

    void setIsbn(const QString& v) { m_isbn = v; }
    void setAuthor(const QString& v) { m_author = v; }
    void setPublisher(const QString& v) { m_publisher = v; }
    void setGenre(const QString& v) { m_genre = v; }

private:
    QString m_isbn;
    QString m_author;
    QString m_publisher;
    QString m_genre;
};

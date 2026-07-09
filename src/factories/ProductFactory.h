#pragma once
#include <memory>
#include <QString>
#include "models/Product.h"












struct ProductData {
    int id = 0;
    QString name;
    double price = 0;
    int stockQty = 0;

    QString isbn, author, publisher, genre;

    int issueNumber = 0;
    QString publishDate;

    QString brand, category;
};

class ProductFactory {
public:

    static std::unique_ptr<Product> create(const QString& type, const ProductData& d);
};

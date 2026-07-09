#include "ProductFactory.h"
#include "models/Book.h"
#include "models/Magazine.h"
#include "models/Stationery.h"

std::unique_ptr<Product> ProductFactory::create(const QString& type, const ProductData& d)
{
    const QString t = type.toUpper();

    if (t == "BOOK")
        return std::make_unique<Book>(d.id, d.name, d.price, d.stockQty,
                                      d.isbn, d.author, d.publisher, d.genre);
    if (t == "MAGAZINE")
        return std::make_unique<Magazine>(d.id, d.name, d.price, d.stockQty,
                                          d.issueNumber, d.publishDate);
    if (t == "STATIONERY")
        return std::make_unique<Stationery>(d.id, d.name, d.price, d.stockQty,
                                            d.brand, d.category);
    return nullptr;
}

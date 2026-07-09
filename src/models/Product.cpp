#include "Product.h"

Product::Product(int id, const QString& name, double price, int stockQty)
    : m_id(id), m_name(name), m_price(0), m_stockQty(0)
{
    setPrice(price);
    setStockQty(stockQty);
}

void Product::setName(const QString& name)
{
    m_name = name.trimmed();
}

void Product::setPrice(double price)
{
    m_price = (price < 0) ? 0 : price;
}

void Product::setStockQty(int qty)
{
    m_stockQty = (qty < 0) ? 0 : qty;
}

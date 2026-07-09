#pragma once
#include <QString>













class Product {
public:
    Product(int id, const QString& name, double price, int stockQty);
    virtual ~Product() = default;


    virtual QString getType() const = 0;


    virtual QString getDetails() const = 0;

    int id() const { return m_id; }
    QString name() const { return m_name; }
    double price() const { return m_price; }
    int stockQty() const { return m_stockQty; }

    void setId(int id) { m_id = id; }
    void setName(const QString& name);
    void setPrice(double price);
    void setStockQty(int qty);


    bool isLowStock(int threshold = 5) const { return m_stockQty <= threshold; }

private:
    int m_id;
    QString m_name;
    double m_price;
    int m_stockQty;
};

#pragma once
#include "Product.h"


class Stationery : public Product {
public:
    Stationery(int id, const QString& name, double price, int stockQty,
               const QString& brand, const QString& category);

    QString getType() const override { return "STATIONERY"; }
    QString getDetails() const override;

    QString brand() const { return m_brand; }
    QString category() const { return m_category; }

    void setBrand(const QString& v) { m_brand = v; }
    void setCategory(const QString& v) { m_category = v; }

private:
    QString m_brand;
    QString m_category;
};

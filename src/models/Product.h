#pragma once
#include <QString>

// Phụ trách: Nguyễn Phúc Lộc
class Product {
public:
    Product(int id, const QString& name, double price, int stockQty);
    virtual ~Product() = default;

    // "BOOK" | "MAGAZINE" | "STATIONERY" — dùng làm cột `type` trong DB
    virtual QString getType() const = 0;

    // Chuỗi mô tả hiển thị trên UI / hoá đơn — mỗi lớp con format khác nhau
    virtual QString getDetails() const = 0;

    int id() const { return m_id; }
    QString name() const { return m_name; }
    double price() const { return m_price; }
    int stockQty() const { return m_stockQty; }

    void setId(int id) { m_id = id; }
    void setName(const QString& name);
    void setPrice(double price);      // không cho giá âm
    void setStockQty(int qty);        // không cho tồn kho âm

    // Tồn kho <= threshold? Dùng cho cảnh báo sắp hết hàng ở ProductPage
    bool isLowStock(int threshold = 5) const { return m_stockQty <= threshold; }

private:
    int m_id;
    QString m_name;
    double m_price;
    int m_stockQty;
};

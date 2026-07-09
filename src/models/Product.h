#pragma once
#include <QString>

/*
 * Product — lớp cơ sở TRỪU TƯỢNG cho mọi sản phẩm trong cửa hàng.
 *
 * Thể hiện 4 tính chất OOP:
 *  - Abstraction   : class trừu tượng, có pure virtual function.
 *  - Encapsulation : thuộc tính private, truy cập qua getter/setter có validate.
 *  - Inheritance   : Book / Magazine / Stationery kế thừa từ Product.
 *  - Polymorphism  : getType()/getDetails() gọi qua con trỏ Product* sẽ chạy
 *                    đúng phiên bản của lớp con (runtime polymorphism).
 *
 * Người phụ trách thiết kế: Member 1 (Lộc)
 */
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

    // Sắp hết hàng? Dùng cho cảnh báo tồn kho (Member 2)
    bool isLowStock(int threshold = 5) const { return m_stockQty <= threshold; }

private:
    int m_id;
    QString m_name;
    double m_price;
    int m_stockQty;
};

#pragma once
#include <memory>
#include <QString>
#include "models/Product.h"

// Gói toàn bộ dữ liệu thô của 1 sản phẩm (đọc từ form hoặc từ DB)
struct ProductData {
    int id = 0;
    QString name;
    double price = 0;
    int stockQty = 0;
    // Book
    QString isbn, author, publisher, genre;
    // Magazine
    int issueNumber = 0;
    QString publishDate;
    // Stationery
    QString brand, category;
};

// Phụ trách: Nguyễn Phúc Lộc
class ProductFactory {
public:
    // type: "BOOK" | "MAGAZINE" | "STATIONERY"; trả về nullptr nếu type sai
    static std::unique_ptr<Product> create(const QString& type, const ProductData& d);
};

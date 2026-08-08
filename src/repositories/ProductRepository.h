#pragma once
#include <memory>
#include <vector>
#include "models/Product.h"
#include "factories/ProductFactory.h"

// Phụ trách: Vũ Bình Nguyên
class ProductRepository {
public:
    // Thêm mới, trả về id vừa tạo (hoặc -1 nếu lỗi)
    int add(const Product& p);

    bool update(const Product& p);
    bool remove(int id);

    std::unique_ptr<Product> findById(int id);
    std::vector<std::unique_ptr<Product>> getAll();

    // Tìm theo tên (LIKE %keyword%), lọc theo type ("" = tất cả)
    std::vector<std::unique_ptr<Product>> search(const QString& keyword,
                                                 const QString& type = QString());

    // Sản phẩm sắp hết hàng (stock_qty <= threshold) — cho cảnh báo tồn kho
    std::vector<std::unique_ptr<Product>> lowStock(int threshold = 5);

    // Trừ tồn kho khi bán, trả về false nếu không đủ hàng. SalesService gọi khi checkout.
    bool decrementStock(int productId, int qty);
};

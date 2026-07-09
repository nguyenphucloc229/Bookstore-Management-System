#pragma once
#include <memory>
#include <vector>
#include "models/Product.h"
#include "factories/ProductFactory.h"

/*
 * ProductRepository — đọc/ghi bảng `products` trong SQLite.
 * UI KHÔNG được viết SQL trực tiếp — mọi truy vấn đi qua đây (separation).
 *
 * NGƯỜI PHỤ TRÁCH: Member 2
 * Gợi ý: dùng QSqlQuery + prepare/bindValue để tránh SQL injection.
 * Khi đọc 1 dòng từ DB -> đổ vào ProductData -> gọi ProductFactory::create().
 */
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

    // Trừ tồn kho khi bán — trả về false nếu không đủ hàng (Member 4 gọi hàm này)
    bool decrementStock(int productId, int qty);
};

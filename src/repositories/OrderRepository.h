#pragma once
#include <memory>
#include <vector>
#include "models/Order.h"

/*
 * OrderRepository — đọc/ghi bảng `orders` + `order_items`.
 * NGƯỜI PHỤ TRÁCH: Member 4
 */
class OrderRepository {
public:
    // Lưu đơn + toàn bộ order_items trong 1 TRANSACTION
    // (nếu 1 item lỗi -> rollback tất cả). Trả về order id hoặc -1.
    int save(const Order& order);

    std::unique_ptr<Order> findById(int id);
    std::vector<std::unique_ptr<Order>> getAll();
    std::vector<std::unique_ptr<Order>> byDateRange(const QDateTime& from,
                                                    const QDateTime& to);
};

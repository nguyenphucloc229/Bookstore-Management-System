#pragma once
#include <QString>
#include "models/Order.h"

/*
 * SalesService — BUSINESS LOGIC BÁN HÀNG (vượt CRUD đơn giản, yêu cầu 3.5).
 *
 * Quy trình checkout:
 *  1. Kiểm tra tồn kho từng item (đủ hàng mới cho bán).
 *  2. Tính tổng tiền của đơn.
 *  3. Lưu Order + OrderItems (transaction).
 *  4. Trừ tồn kho từng sản phẩm.
 *
 * NGƯỜI PHỤ TRÁCH: Tân (Member 4)
 */
class SalesService {
public:
    struct CheckoutResult {
        bool success = false;
        int orderId = -1;
        QString errorMessage;   // hiển thị lên UI nếu thất bại
    };

    CheckoutResult checkout(Order& order);

    // Sinh nội dung hoá đơn dạng text để hiển thị/in (yêu cầu receipt trong đề)
    QString buildReceipt(const Order& order) const;
};

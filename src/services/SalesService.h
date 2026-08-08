#pragma once
#include <QString>
#include "models/Order.h"

// Phụ trách: Võ Viết Tân
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

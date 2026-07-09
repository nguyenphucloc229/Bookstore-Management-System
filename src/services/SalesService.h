#pragma once
#include <QString>
#include "models/Order.h"












class SalesService {
public:
    struct CheckoutResult {
        bool success = false;
        int orderId = -1;
        QString errorMessage;
    };

    CheckoutResult checkout(Order& order);


    QString buildReceipt(const Order& order) const;
};

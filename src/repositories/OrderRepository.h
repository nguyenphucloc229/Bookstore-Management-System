#pragma once
#include <memory>
#include <vector>
#include "models/Order.h"





class OrderRepository {
public:


    int save(const Order& order);

    std::unique_ptr<Order> findById(int id);
    std::vector<std::unique_ptr<Order>> getAll();
    std::vector<std::unique_ptr<Order>> byDateRange(const QDateTime& from,
                                                    const QDateTime& to);
};

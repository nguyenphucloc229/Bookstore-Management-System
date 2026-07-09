#pragma once
#include <memory>
#include <vector>
#include "models/Customer.h"

/*
 * CustomerRepository — đọc/ghi bảng `customers`.
 * NGƯỜI PHỤ TRÁCH: Member 3
 */
class CustomerRepository {
public:
    int add(const Customer& c);
    bool update(const Customer& c);
    bool remove(int id);

    std::unique_ptr<Customer> findById(int id);
    std::vector<std::unique_ptr<Customer>> getAll();
    std::vector<std::unique_ptr<Customer>> search(const QString& keyword); // theo tên/SĐT
};

#pragma once
#include <memory>
#include <vector>
#include "models/Product.h"
#include "factories/ProductFactory.h"









class ProductRepository {
public:

    int add(const Product& p);

    bool update(const Product& p);
    bool remove(int id);

    std::unique_ptr<Product> findById(int id);
    std::vector<std::unique_ptr<Product>> getAll();


    std::vector<std::unique_ptr<Product>> search(const QString& keyword,
                                                 const QString& type = QString());


    std::vector<std::unique_ptr<Product>> lowStock(int threshold = 5);


    bool decrementStock(int productId, int qty);
};

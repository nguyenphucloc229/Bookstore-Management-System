#include "ProductRepository.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>


















int ProductRepository::add(const Product& p)
{
    (void)p;
    return -1;
}

bool ProductRepository::update(const Product& p)
{
    (void)p;
    return false;
}

bool ProductRepository::remove(int id)
{
    (void)id;
    return false;
}

std::unique_ptr<Product> ProductRepository::findById(int id)
{
    (void)id;
    return nullptr;
}

std::vector<std::unique_ptr<Product>> ProductRepository::getAll()
{
    return {};
}

std::vector<std::unique_ptr<Product>> ProductRepository::search(const QString& keyword,
                                                                const QString& type)
{
    (void)keyword; (void)type;
    return {};
}

std::vector<std::unique_ptr<Product>> ProductRepository::lowStock(int threshold)
{
    (void)threshold;
    return {};
}

bool ProductRepository::decrementStock(int productId, int qty)
{
    (void)productId; (void)qty;
    return false;
}

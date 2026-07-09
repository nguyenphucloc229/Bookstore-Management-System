#include "OrderRepository.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>









int OrderRepository::save(const Order& order)
{
    (void)order;
    return -1;
}

std::unique_ptr<Order> OrderRepository::findById(int id)
{
    (void)id;
    return nullptr;
}

std::vector<std::unique_ptr<Order>> OrderRepository::getAll()
{
    return {};
}

std::vector<std::unique_ptr<Order>> OrderRepository::byDateRange(const QDateTime& from,
                                                                 const QDateTime& to)
{
    (void)from; (void)to;
    return {};
}

#include "CustomerRepository.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>


int CustomerRepository::add(const Customer& c)
{
    (void)c;
    return -1; 
}

bool CustomerRepository::update(const Customer& c)
{
    (void)c;
    return false; 
}

bool CustomerRepository::remove(int id)
{
    (void)id;
    return false; 
}

std::unique_ptr<Customer> CustomerRepository::findById(int id)
{
    (void)id;
    return nullptr; 
}

std::vector<std::unique_ptr<Customer>> CustomerRepository::getAll()
{
    return {}; 
}

std::vector<std::unique_ptr<Customer>> CustomerRepository::search(const QString& keyword)
{
    (void)keyword;
    return {}; 

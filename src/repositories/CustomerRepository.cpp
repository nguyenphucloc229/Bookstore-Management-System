#include "CustomerRepository.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>


int CustomerRepository::add(const Customer& c)
{
    QSqlQuery q(DatabaseManager::instance().db());

    q.prepare(R"(
        INSERT INTO customers(name, phone, email)
        VALUES(?, ?, ?)
    )");

    q.addBindValue(c.name());
    q.addBindValue(c.phone());
    q.addBindValue(c.email());

    if (!q.exec()) {
        qWarning() << q.lastError().text();
        return -1;
    }

    return q.lastInsertId().toInt();
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
    std::vector<std::unique_ptr<Customer>> customers;

    QSqlQuery q(DatabaseManager::instance().db());

    if (!q.exec("SELECT id, name, phone, email FROM customers ORDER BY id")) {
        qWarning() << q.lastError().text();
        return customers;
    }

    while (q.next()) {
        customers.push_back(std::make_unique<Customer>(
            q.value(0).toInt(),
            q.value(1).toString(),
            q.value(2).toString(),
            q.value(3).toString()
            ));
    }

    return customers;
}

std::vector<std::unique_ptr<Customer>> CustomerRepository::search(const QString& keyword)
{
    std::vector<std::unique_ptr<Customer>> customers;

    QSqlQuery q(DatabaseManager::instance().db());

    q.prepare(R"(
        SELECT id, name, phone, email
        FROM customers
        WHERE name LIKE ?
           OR phone LIKE ?
        ORDER BY id
    )");

    QString k = "%" + keyword + "%";
    q.addBindValue(k);
    q.addBindValue(k);

    if (!q.exec()) {
        qWarning() << q.lastError().text();
        return customers;
    }

    while (q.next()) {
        customers.push_back(std::make_unique<Customer>(
            q.value(0).toInt(),
            q.value(1).toString(),
            q.value(2).toString(),
            q.value(3).toString()
            ));
    }

    return customers;
}

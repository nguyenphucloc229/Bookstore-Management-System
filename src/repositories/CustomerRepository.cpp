#include "CustomerRepository.h"
#include "db/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int CustomerRepository::add(const Customer &customer)
{
    QSqlQuery query(DatabaseManager::instance().db());

    if (!query.prepare(R"(
        INSERT INTO customers
            (name, phone, email, point, rank)
        VALUES
            (?, ?, ?, ?, ?)
    )"))
    {
        qDebug() << "Prepare add customer failed:"
                 << query.lastError().text();
        return -1;
    }

    query.addBindValue(customer.name());
    query.addBindValue(customer.phone());
    query.addBindValue(customer.email());
    query.addBindValue(customer.point());
    query.addBindValue(customer.rank());

    if (!query.exec())
    {
        qDebug() << "Add customer failed:"
                 << query.lastError().text();

        qDebug() << "Query:"
                 << query.lastQuery();

        return -1;
    }

    return query.lastInsertId().toInt();
}

bool CustomerRepository::update(const Customer &customer)
{
    QSqlQuery query;

    query.prepare(R"(
        UPDATE customers
        SET name = ?,
            phone = ?,
            email = ?,
            point = ?,
            rank = ?
        WHERE id = ?
    )");

    query.addBindValue(customer.name());
    query.addBindValue(customer.phone());
    query.addBindValue(customer.email());
    query.addBindValue(customer.point());
    query.addBindValue(customer.rank());
    query.addBindValue(customer.id());

    if (!query.exec())
    {
        qDebug() << "Update customer failed:"
                 << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool CustomerRepository::remove(int id)
{
    QSqlQuery q(DatabaseManager::instance().db());

    q.prepare("DELETE FROM customers WHERE id = ?");
    q.addBindValue(id);

    if (!q.exec()) {
        qWarning() << q.lastError().text();
        return false;
    }

    return q.numRowsAffected() > 0;
}

std::unique_ptr<Customer> CustomerRepository::findById(int id)
{
    QSqlQuery query;

    query.prepare(R"(
        SELECT id, name, phone, email, point, rank
        FROM customers
        WHERE id = ?
    )");

    query.addBindValue(id);

    if (!query.exec())
    {
        qDebug() << "findById query error:"
                 << query.lastError().text();
        return nullptr;
    }

    if (!query.next())
    {
        qDebug() << "Không tìm thấy khách hàng có ID:" << id;
        return nullptr;
    }

    return std::make_unique<Customer>(
        query.value("id").toInt(),
        query.value("name").toString(),
        query.value("phone").toString(),
        query.value("email").toString(),
        query.value("point").toInt(),
        query.value("rank").toString()
        );
}

std::vector<std::unique_ptr<Customer>>
CustomerRepository::getAll()
{
    std::vector<std::unique_ptr<Customer>> customers;

    QSqlQuery query(DatabaseManager::instance().db());

    if (!query.exec(R"(
        SELECT id, name, phone, email, point, rank
        FROM customers
        ORDER BY id DESC
    )"))
    {
        qDebug() << "getAll query error:"
                 << query.lastError().text();
        return customers;
    }

    while (query.next())
    {
        customers.push_back(
            std::make_unique<Customer>(
                query.value("id").toInt(),
                query.value("name").toString(),
                query.value("phone").toString(),
                query.value("email").toString(),
                query.value("point").toInt(),
                query.value("rank").toString()
                )
            );
    }

    return customers;
}

std::vector<std::unique_ptr<Customer>> CustomerRepository::search(const QString &keyword)
{
    std::vector<std::unique_ptr<Customer>> customers;

    QSqlQuery query;

    query.prepare(R"(
        SELECT id, name, phone, email, point, rank
        FROM customers
        WHERE name LIKE ?
           OR phone LIKE ?
        ORDER BY id DESC
    )");

    QString value = "%" + keyword.trimmed() + "%";

    query.addBindValue(value);
    query.addBindValue(value);

    if (!query.exec())
    {
        qDebug() << "search query error:"
                 << query.lastError().text();
        return customers;
    }

    while (query.next())
    {
        customers.push_back(
            std::make_unique<Customer>(
                query.value("id").toInt(),
                query.value("name").toString(),
                query.value("phone").toString(),
                query.value("email").toString(),
                query.value("point").toInt(),
                query.value("rank").toString()
                )
            );
    }

    return customers;
}
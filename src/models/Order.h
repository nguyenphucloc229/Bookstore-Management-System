#pragma once
#include <QString>
#include <QDateTime>
#include <QVector>





struct OrderItem {
    int productId = 0;
    QString productName;
    double unitPrice = 0;
    int quantity = 0;

    double lineTotal() const { return unitPrice * quantity; }
};





class Order {
public:
    Order() = default;
    Order(int id, int customerId, const QDateTime& createdAt);

    int id() const { return m_id; }
    int customerId() const { return m_customerId; }
    QDateTime createdAt() const { return m_createdAt; }
    const QVector<OrderItem>& items() const { return m_items; }

    void setId(int id) { m_id = id; }
    void setCustomerId(int id) { m_customerId = id; }
    void setCreatedAt(const QDateTime& t) { m_createdAt = t; }

    void addItem(const OrderItem& item);
    void removeItemAt(int index);
    void clearItems() { m_items.clear(); }


    double subtotal() const;


    double total() const { return subtotal(); }

private:
    int m_id = 0;
    int m_customerId = 0;
    QDateTime m_createdAt;
    QVector<OrderItem> m_items;
};

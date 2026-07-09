#pragma once
#include <QString>
#include <QDateTime>
#include <QVector>

/*
 * OrderItem — 1 dòng trong đơn hàng.
 * Lưu "snapshot" tên + giá tại thời điểm bán (giá sản phẩm có thể đổi sau này).
 */
struct OrderItem {
    int productId = 0;
    QString productName;
    double unitPrice = 0;
    int quantity = 0;

    double lineTotal() const { return unitPrice * quantity; }
};

/*
 * Order — đơn hàng, chứa nhiều OrderItem (quan hệ Composition).
 * Người phụ trách logic bán hàng: Tân (Member 4).
 */
class Order {
public:
    Order() = default;
    Order(int id, int customerId, const QDateTime& createdAt);

    int id() const { return m_id; }
    int customerId() const { return m_customerId; }     // 0 = khách vãng lai
    QDateTime createdAt() const { return m_createdAt; }
    const QVector<OrderItem>& items() const { return m_items; }

    void setId(int id) { m_id = id; }
    void setCustomerId(int id) { m_customerId = id; }
    void setCreatedAt(const QDateTime& t) { m_createdAt = t; }

    void addItem(const OrderItem& item);
    void removeItemAt(int index);
    void clearItems() { m_items.clear(); }

    // Tổng tiền của đơn = tổng các dòng
    double subtotal() const;

    // Thành tiền (scope tối thiểu không có giảm giá nên total = subtotal)
    double total() const { return subtotal(); }

private:
    int m_id = 0;
    int m_customerId = 0;
    QDateTime m_createdAt;
    QVector<OrderItem> m_items;
};

#include "Order.h"

Order::Order(int id, int customerId, const QDateTime& createdAt)
    : m_id(id), m_customerId(customerId), m_createdAt(createdAt)
{
}

void Order::addItem(const OrderItem& item)
{
    // Nếu sản phẩm đã có trong đơn thì cộng dồn số lượng
    for (auto& it : m_items) {
        if (it.productId == item.productId) {
            it.quantity += item.quantity;
            return;
        }
    }
    m_items.append(item);
}

void Order::removeItemAt(int index)
{
    if (index >= 0 && index < m_items.size())
        m_items.removeAt(index);
}

double Order::subtotal() const
{
    double sum = 0;
    for (const auto& it : m_items)
        sum += it.lineTotal();
    return sum;
}

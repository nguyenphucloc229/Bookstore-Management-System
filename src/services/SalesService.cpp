#include "SalesService.h"
#include "repositories/ProductRepository.h"
#include "repositories/OrderRepository.h"
#include <QTextStream>
// TODO(Member 4 - Tân): implement theo quy trình mô tả trong SalesService.h
SalesService::CheckoutResult SalesService::checkout(Order& order)
{
    CheckoutResult result;

    // Bước 1: Kiểm tra tồn kho từng item
    // TODO(Member 2): dùng ProductRepository::findById(...)
    // để kiểm tra stock_qty có đủ hay không.

    // Bước 2: Tính tổng tiền
    // Order::total() đã tính tổng từ các OrderItem.
    const double total = order.total();
    (void)total;

    // Bước 3: Lưu Order + OrderItems
    OrderRepository orderRepo;
    const int orderId = orderRepo.save(order);

    if (orderId < 0) {
        result.errorMessage = "Không thể lưu đơn hàng.";
        return result;
    }

    // Bước 4: Trừ tồn kho
    // TODO(Member 2): gọi ProductRepository::decrementStock(...)
    // cho từng item sau khi repository hoàn thiện.

    result.success = true;
    result.orderId = orderId;
    return result;
}

QString SalesService::buildReceipt(const Order& order) const
{
    QString receipt;
    QTextStream out(&receipt);

    out << "BOOKSTORE MANAGEMENT SYSTEM\n";
    out << "========================================\n";
    out << "Ngày: "
        << order.createdAt().toString("dd/MM/yyyy HH:mm:ss")
        << "\n";

    if (order.customerId() == 0) {
        out << "Khach hang: Khach vang lai\n";
    } else {
        out << "Ma khach hang: " << order.customerId() << "\n";
    }

    out << "========================================\n";
    out << "San pham\tSL\tDon gia\tThanh tien\n";
    out << "----------------------------------------\n";

    for (const OrderItem& item : order.items()) {
        out << item.productName << "\n";
        out << "\t"
            << item.quantity << "\t"
            << QString::number(item.unitPrice, 'f', 2) << "\t"
            << QString::number(item.lineTotal(), 'f', 2)
            << "\n";
    }

    out << "----------------------------------------\n";
    out << "TONG TIEN: "
        << QString::number(order.total(), 'f', 2)
        << "\n";
    out << "========================================\n";

    return receipt;
}
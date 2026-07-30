#include "SalesService.h"
#include "repositories/OrderRepository.h"
#include "repositories/ProductRepository.h"
#include "repositories/CustomerRepository.h"

#include <QTextStream>

SalesService::CheckoutResult SalesService::checkout(Order& order)
{
    CheckoutResult result;

    if (order.items().empty()) {
        result.errorMessage = "Đơn hàng không có sản phẩm.";
        return result;
    }

    ProductRepository productRepo;

    // Bước 1: Kiểm tra tồn kho từng item TRƯỚC khi bán
    for (const OrderItem& item : order.items()) {
        auto product = productRepo.findById(item.productId);
        if (!product) {
            result.errorMessage =
                QString("Sản phẩm '%1' không còn tồn tại.").arg(item.productName);
            return result;
        }
        if (product->stockQty() < item.quantity) {
            result.errorMessage =
                QString("Không đủ tồn kho cho '%1' (còn %2, cần %3).")
                    .arg(item.productName)
                    .arg(product->stockQty())
                    .arg(item.quantity);
            return result;
        }
    }

    // Bước 2: Lưu Order + OrderItems (transaction trong OrderRepository)
    OrderRepository orderRepo;
    const int orderId = orderRepo.save(order);
    if (orderId < 0) {
        result.errorMessage = "Không thể lưu đơn hàng.";
        return result;
    }
    order.setId(orderId);

    // Bước 3: Trừ tồn kho từng sản phẩm (đã kiểm tra đủ hàng ở Bước 1)
    for (const OrderItem& item : order.items()) {
        productRepo.decrementStock(item.productId, item.quantity);
    }

    // Bước 4: Cộng điểm cho khách thành viên (1 điểm / 10.000đ) + cập nhật hạng
    if (order.customerId() != 0) {
        CustomerRepository customerRepo;
        auto customer = customerRepo.findById(order.customerId());
        if (customer) {
            const int earned = static_cast<int>(order.total() / 10000.0);
            if (earned > 0) {
                customer->setPoint(customer->point() + earned);
                customer->updateRank();
                customerRepo.update(*customer);
            }
        }
    }

    result.success = true;
    result.orderId = orderId;
    return result;
}

QString SalesService::buildReceipt(const Order& order) const
{
    QString receipt;
    QTextStream out(&receipt);

    out << "HỆ THỐNG QUẢN LÝ NHÀ SÁCH\n";
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

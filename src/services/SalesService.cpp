#include "SalesService.h"
#include "repositories/ProductRepository.h"
#include "repositories/OrderRepository.h"

// TODO(Member 4 - Tân): implement theo quy trình mô tả trong SalesService.h

SalesService::CheckoutResult SalesService::checkout(Order& order)
{
    (void)order;
    CheckoutResult r;
    r.errorMessage = "Chưa implement"; // TODO(Member 4)
    return r;
}

QString SalesService::buildReceipt(const Order& order) const
{
    (void)order;
    // TODO(Member 4): format hoá đơn — tên cửa hàng, ngày giờ, bảng item
    // (tên, SL, đơn giá, thành tiền), và TỔNG tiền.
    // Mẹo: duyệt order.items() và dùng QString::arg với độ rộng cố định.
    return "TODO";
}

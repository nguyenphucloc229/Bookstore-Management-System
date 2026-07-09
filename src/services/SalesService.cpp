#include "SalesService.h"
#include "repositories/ProductRepository.h"
#include "repositories/OrderRepository.h"



SalesService::CheckoutResult SalesService::checkout(Order& order)
{
    (void)order;
    CheckoutResult r;
    r.errorMessage = "Chưa implement";
    return r;
}

QString SalesService::buildReceipt(const Order& order) const
{
    (void)order;



    return "TODO";
}

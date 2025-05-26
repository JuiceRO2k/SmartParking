#ifndef PAYMENT_H
#define PAYMENT_H

#include <memory>
#include "Ticket.h"

class Payment {
    int id;
    std::shared_ptr<Ticket> ticket;
    double amount;

public:
    Payment(int id, std::shared_ptr<Ticket> t);
    void process();
    double getAmount() const { return amount; }
};

#endif // PAYMENT_H

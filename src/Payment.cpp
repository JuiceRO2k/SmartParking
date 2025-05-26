#include "Payment.h"
#include <iostream>
using namespace std;

Payment::Payment(int id, shared_ptr<Ticket> t)
    : id(id), ticket(t), amount(0) {}

void Payment::process() {
    amount = ticket->calculateFee();
    ticket->setPaid(true);
    cout << "Plata in valoare de " << amount << " lei a fost efectuata.\n";
}

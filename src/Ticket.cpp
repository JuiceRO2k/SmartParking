#include "Ticket.h"
using namespace std;

Ticket::Ticket(int id,
               shared_ptr<Vehicle> v,
               shared_ptr<ParkingSpot> s)
    : id(id), vehicle(v), spot(s),
      start(chrono::system_clock::now())
{}

void Ticket::checkOut() {
    end = chrono::system_clock::now();
    checkedOut = true;
}

double Ticket::calculateFee() const {
    using namespace chrono;
    auto dur = duration_cast<hours>(end - start).count() + 1;
    return dur * 5.0;
}

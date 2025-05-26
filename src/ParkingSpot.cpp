#include "ParkingSpot.h"
#include "Ticket.h"
using namespace std;

ParkingSpot::ParkingSpot(int id, int lvl, int row, SpotType t)
    : id(id), level(lvl), row(row), type(t), occupied(false) {}

int ParkingSpot::getId() const { return id; }
SpotType ParkingSpot::getType() const { return type; }
bool ParkingSpot::isOccupied() const { return occupied; }

void ParkingSpot::park(shared_ptr<Ticket> t) {
    currentTicket = t;
    occupied = true;
}

void ParkingSpot::leave() {
    currentTicket.reset();
    occupied = false;
}

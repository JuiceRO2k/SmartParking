#include "Reservation.h"
using namespace std;

Reservation::Reservation(int id,
                         shared_ptr<Client> c,
                         shared_ptr<ParkingSpot> s,
                         chrono::minutes duration)
    : id(id), client(c), spot(s) {
    expireAt = chrono::system_clock::now() + duration;
}

bool Reservation::isActive() const {
    return chrono::system_clock::now() < expireAt;
}

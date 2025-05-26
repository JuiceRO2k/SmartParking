#ifndef RESERVATION_H
#define RESERVATION_H

#include <memory>
#include <chrono>
#include "Client.h"
#include "ParkingSpot.h"
using namespace std;

class Reservation {
    int id;
    shared_ptr<Client> client;
    shared_ptr<ParkingSpot> spot;
    chrono::system_clock::time_point expireAt;

    public:
        Reservation(int id,
                    shared_ptr<Client> c,
                    shared_ptr<ParkingSpot> s,
                    chrono::minutes duration);
        bool isActive() const;
};

#endif // RESERVATION_H

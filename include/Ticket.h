#ifndef TICKET_H
#define TICKET_H

#include <memory>
#include <chrono>
#include "Vehicle.h"
#include "ParkingSpot.h"

class Ticket {
    int id;
    std::shared_ptr<Vehicle> vehicle;
    std::shared_ptr<ParkingSpot> spot;
    std::chrono::system_clock::time_point start, end;
    bool paid      = false;
    bool checkedOut = false;

public:
    Ticket(int id,
           std::shared_ptr<Vehicle> v,
           std::shared_ptr<ParkingSpot> s);

    void checkOut();

    double calculateFee() const;

    void   setPaid(bool p)       { paid = p; }
    bool   isPaid()      const   { return paid; }
    bool   isCheckedOut() const  { return checkedOut; }

    int    getId()       const   { return id; }
    auto   getVehicle()  const   { return vehicle; }
    auto   getSpot()     const   { return spot; }
};

#endif // TICKET_H

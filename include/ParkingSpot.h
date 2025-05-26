#ifndef PARKINGSPOT_H
#define PARKINGSPOT_H

#include "Vehicle.h"
#include <memory>
using namespace std;

enum class SpotType { Standard, Motorcycle, Utility };

class Ticket;

class ParkingSpot {
    int id;
    int level, row;
    SpotType type;
    bool occupied;
    shared_ptr<Ticket> currentTicket;
    
    public:
        ParkingSpot(int id, int lvl, int row, SpotType t);
        int getId() const;
        SpotType getType() const;
        bool isOccupied() const;
        void park(shared_ptr<Ticket> t);
        void leave();
};

#endif // PARKINGSPOT_H

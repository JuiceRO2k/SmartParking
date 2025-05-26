#include "ParkingLot.h"
using namespace std;

ParkingLot::ParkingLot(int id, const string& name)
    : id(id), name(name) {}

int ParkingLot::getId() const {
    return id;
}

const string& ParkingLot::getName() const {
    return name;
}

const vector<shared_ptr<ParkingSpot>>&
ParkingLot::getSpots() const {
    return spots;
}

void ParkingLot::addSpot(shared_ptr<ParkingSpot> s) {
    spots.push_back(s);
}

vector<shared_ptr<ParkingSpot>>
ParkingLot::getAvailableSpots() const {
    vector<shared_ptr<ParkingSpot>> free;
    for (auto& s : spots)
        if (!s->isOccupied())
            free.push_back(s);
    return free;
}

shared_ptr<ParkingSpot>
ParkingLot::findSpotById(int sid) const {
    for (auto& s : spots)
        if (s->getId() == sid)
            return s;
    return nullptr;
}

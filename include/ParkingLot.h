#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <vector>
#include <memory>
#include <string>
#include "ParkingSpot.h"

class ParkingLot {
    int id;
    std::string name;
    std::vector<std::shared_ptr<ParkingSpot>> spots;

public:
    ParkingLot(int id, const std::string& name);
    int getId() const;
    const std::string& getName() const;
    const std::vector<std::shared_ptr<ParkingSpot>>& getSpots() const;

    void addSpot(std::shared_ptr<ParkingSpot> s);
    std::vector<std::shared_ptr<ParkingSpot>> getAvailableSpots() const;
    std::shared_ptr<ParkingSpot> findSpotById(int id) const;
};

#endif // PARKINGLOT_H

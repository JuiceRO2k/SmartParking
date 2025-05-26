#include "Vehicle.h"
using namespace std;

Vehicle::Vehicle(int id, const string& plate, VehicleType t)
    : id(id), licensePlate(plate), type(t) {}

int Vehicle::getId() const { return id; }
string Vehicle::getPlate() const { return licensePlate; }
VehicleType Vehicle::getType() const { return type; }

Car::Car(int id, const string& plate)
    : Vehicle(id, plate, VehicleType::Car) {}

Motorcycle::Motorcycle(int id, const string& plate)
    : Vehicle(id, plate, VehicleType::Motorcycle) {}

Truck::Truck(int id, const string& plate)
    : Vehicle(id, plate, VehicleType::Truck) {}

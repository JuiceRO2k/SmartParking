#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

enum class VehicleType { Car, Motorcycle, Truck };

class Vehicle {
    protected:
        int id;
        string licensePlate;
        VehicleType type;
    public:
        Vehicle(int id, const string& plate, VehicleType t);
        virtual ~Vehicle() = default;

        int getId() const;
        string getPlate() const;
        VehicleType getType() const;
};

class Car : public Vehicle {
    public:
        Car(int id, const string& plate);
};

class Motorcycle : public Vehicle {
    public:
        Motorcycle(int id, const string& plate);
};

class Truck : public Vehicle {
    public:
        Truck(int id, const string& plate);
};

#endif // VEHICLE_H

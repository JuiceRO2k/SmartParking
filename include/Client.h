#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <memory>
#include "Vehicle.h"
using namespace std;

class Client {
    int id;
    string name;
    vector<shared_ptr<Vehicle>> vehicles;
    
    public:
        Client(int id, const string& name);
        int getId() const;
        string getName() const;
        void addVehicle(shared_ptr<Vehicle> v);
        const vector<shared_ptr<Vehicle>>& getVehicles() const;
};

#endif // CLIENT_H

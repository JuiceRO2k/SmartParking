#include "Client.h"
using namespace std;

Client::Client(int id, const string& name)
    : id(id), name(name) {}

int Client::getId() const { return id; }
string Client::getName() const { return name; }
void Client::addVehicle(shared_ptr<Vehicle> v) {
    vehicles.push_back(v);
}
const vector<shared_ptr<Vehicle>>&
Client::getVehicles() const { return vehicles; }

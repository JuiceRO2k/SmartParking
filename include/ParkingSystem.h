#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include <vector>
#include <map>
#include <memory>
#include "Client.h"
#include "Vehicle.h"
#include "ParkingLot.h"
#include "Ticket.h"
#include "Reservation.h"
#include "Payment.h"

class ParkingSystem {
    std::map<int, std::shared_ptr<Client>> clients;
    std::vector<std::shared_ptr<ParkingLot>> lots;
    std::vector<std::shared_ptr<Ticket>> tickets;
    std::vector<std::shared_ptr<Reservation>> reservations;
    std::vector<std::shared_ptr<Payment>> payments;

    int nextClientId  = 1;
    int nextVehicleId = 1;
    int nextTicketId  = 1;
    int nextResId     = 1;
    int nextPayId     = 1;
    int nextLotId     = 1;

    std::shared_ptr<ParkingLot> activeLot;

public:
    void initSampleData();
    void run();

private:
    void cmdCreateClient();
    void cmdAddVehicle();

    void cmdCreateParking();
    void cmdSelectActiveParking();
    void cmdShowVehicles();

    void cmdShowAvailable();
    void cmdReserve();
    void cmdParkVehicle();
    void cmdPay();
    void cmdCheckOut();
    void cmdAdminReportActive();

    void cmdAdminReport();
    void cmdGlobalReport();
};

#endif // PARKINGSYSTEM_H

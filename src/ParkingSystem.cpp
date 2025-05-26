#include "ParkingSystem.h"
#include <iostream>
#include <cstdlib>    
#include <limits>     
#include <regex>
#include <algorithm>
using namespace std;

static void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ParkingSystem::initSampleData() {
    auto lot = make_shared<ParkingLot>(nextLotId++, "Parcare Principala");
    int id = 1;
    // nivel 0, 6 randuri x 5 coloane
    for (int lvl = 0; lvl < 1; ++lvl) {
        for (int r = 0; r < 6; ++r) {
            for (int c = 0; c < 5; ++c) {
                lot->addSpot(make_shared<ParkingSpot>(id++, lvl, r, SpotType::Standard));
            }
        }
    }
    lots.push_back(lot);
    activeLot = lot;
}

void ParkingSystem::run() {
    initSampleData();
    while (true) {
        cout << "\n=== Smart Parking Menu ===\n"
                  << "1. Creare client\n"
                  << "2. Adauga vehicul\n"
                  << "3. Creare parcare (clasic/etajata)\n"
                  << "4. Selectare parcare activa\n"
                  << "5. Arata locuri libere\n"
                  << "6. Rezervare loc\n"
                  << "7. Parcare vehicul\n"
                  << "8. Checkout\n"
                  << "9. Plata\n"
                  << "10. Vizualizare vehicule inregistrate\n"
                  << "11. Raport admin (parcare activa)\n"
                  << "12. Raport total\n"
                  << "0. Iesire\n"
                  << "Alege: ";
        int cmd;
        cin >> cmd;

        clearConsole();

        if (cmd == 0) {
            return;
        }

        cout << " \n";
        switch (cmd) {
            case 1:  cmdCreateClient();        break;
            case 2:  cmdAddVehicle();          break;
            case 3:  cmdCreateParking();       break;
            case 4:  cmdSelectActiveParking(); break;
            case 5:  cmdShowAvailable();       break;
            case 6:  cmdReserve();             break;
            case 7:  cmdParkVehicle();         break;
            case 8:  cmdCheckOut();            break;
            case 9:  cmdPay();                 break;
            case 10: cmdShowVehicles();        break;
            case 11: cmdAdminReportActive();   break;
            case 12: cmdGlobalReport();      break;
            default: cout << "Comanda invalida\n";
        }

        cout << "\nApasa Enter pentru a reveni la meniu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        clearConsole();
    }
}

void ParkingSystem::cmdCreateClient() {
    string name;
    cout << "Nume client: ";
    cin >> ws;            
    getline(cin, name);   

    for (const auto& kv : clients) {
        if (kv.second->getName() == name) {
            cout << "Eroare: exista deja un client cu numele \"" 
                      << name << "\".\n";
            return;
        }
    }

    auto c = make_shared<Client>(nextClientId++, name);
    clients[c->getId()] = c;
    cout << "Client creat cu ID=" << c->getId() << "\n";
}

void ParkingSystem::cmdAddVehicle() {
    int cid;
    cout << "ID client: ";
    cin >> cid;
    auto it = clients.find(cid);
    if (it == clients.end()) {
        cout << "Client invalid\n";
        return;
    }

    string plate;
    cout << "Numar inmatriculare (format RO, ex. B12ABC): ";
    cin >> plate;
    transform(plate.begin(), plate.end(), plate.begin(), ::toupper);

    static const regex romPlate("^[A-Z]{1,2}[0-9]{2}[A-Z]{3}$");
    if (!regex_match(plate, romPlate)) {
        cout << "Format placuta invalid. Trebuie sa fie de forma 'AA12ABC'.\n";
        return;
    }

    for (auto& kv : clients) {
        for (auto& v : kv.second->getVehicles()) {
            if (v->getPlate() == plate) {
                cout << "Eroare: exista deja un vehicul inregistrat cu numarul " 
                          << plate << ".\n";
                return;
            }
        }
    }

    cout << "Tip vehicul (0=Car, 1=Motor, 2=Truck): ";
    int vt; 
    cin >> vt;

    shared_ptr<Vehicle> v;
    if (vt == 0)      v = make_shared<Car>(nextVehicleId++, plate);
    else if (vt == 1) v = make_shared<Motorcycle>(nextVehicleId++, plate);
    else              v = make_shared<Truck>(nextVehicleId++, plate);

    it->second->addVehicle(v);
    cout << "Vehicul adaugat cu ID=" << v->getId() 
              << " si numar " << plate << "\n";
}

void ParkingSystem::cmdCreateParking() {
    cout << "Nume parcare: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    getline(cin, name);

    cout << "Tip parcare (1=Clasic, 2=Etajata): ";
    int t; cin >> t;

    auto lot = make_shared<ParkingLot>(nextLotId++, name);
    int id = 1;
    const int rows = 6, cols = 5;
    if (t == 1) {
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                lot->addSpot(make_shared<ParkingSpot>(id++, 0, r, SpotType::Standard));
    } else {
        cout << "Cate niveluri (max 3): ";
        int nivele; cin >> nivele;
        if (nivele > 3) nivele = 3;
        for (int lvl = 0; lvl < nivele; ++lvl)
            for (int r = 0; r < rows; ++r)
                for (int c = 0; c < cols; ++c)
                    lot->addSpot(make_shared<ParkingSpot>(id++, lvl, r, SpotType::Standard));
    }

    lots.push_back(lot);
    activeLot = lot;
    cout << "Parcare '" << lot->getName()
              << "' creata si setata activa (ID=" << lot->getId() << ")\n";
}

void ParkingSystem::cmdSelectActiveParking() {
    cout << "Parcari disponibile:\n";
    for (auto& lot : lots) {
        cout << " - ID=" << lot->getId()
                  << " : " << lot->getName() << "\n";
    }
    cout << "Alege ID parcare: ";
    int id; cin >> id;
    for (auto& lot : lots) {
        if (lot->getId() == id) {
            activeLot = lot;
            cout << "Parcare activa: " << lot->getName() << "\n";
            return;
        }
    }
    cout << "ID necunoscut\n";
}

void ParkingSystem::cmdShowVehicles() {
    cout << "=== Vehicule inregistrate ===\n";
    for (auto& kv : clients) {
        int cid = kv.first;
        auto cli = kv.second;
        cout << "Client " << cid
                  << " (" << cli->getName() << "):\n";
        for (auto& v : cli->getVehicles()) {
            cout << "   - Veh ID=" << v->getId()
                      << ", Plate=" << v->getPlate() << "\n";
        }
    }
}

void ParkingSystem::cmdShowAvailable() {
    if (!activeLot) {
        cout << "Selectati mai intai o parcare activa!\n";
        return;
    }
    auto free = activeLot->getAvailableSpots();
    cout << "Parcare '" << activeLot->getName()
              << "': " << free.size() << " locuri libere\n";
}

void ParkingSystem::cmdReserve() {
    if (!activeLot) {
        cout << "Selectati o parcare activa!\n";
        return;
    }
    int cid, sid;
    cout << "Client ID: "; cin >> cid;
    cout << "Spot ID:   "; cin >> sid;

    auto cit = clients.find(cid);
    if (cit == clients.end()) {
        cout << "Client invalid\n";
        return;
    }
    auto spot = activeLot->findSpotById(sid);
    if (!spot) {
        cout << "Spot invalid\n";
        return;
    }
    if (spot->isOccupied()) {
        cout << "Spot deja ocupat!\n";
        return;
    }

    auto r = make_shared<Reservation>(
        nextResId++, cit->second, spot, chrono::minutes(30)
    );
    reservations.push_back(r);
    cout << "Rezervare creata OK\n";
}

void ParkingSystem::cmdParkVehicle() {
    if (!activeLot) {
        cout << "Selectati o parcare activa!\n";
        return;
    }
    int vid, sid;
    cout << "Vehicle ID: "; cin >> vid;
    cout << "Spot ID:    "; cin >> sid;

    for (auto& t : tickets) {
        if (!t->isCheckedOut() && t->getVehicle()->getId() == vid) {
            cout << "Vehiculul este deja parcat!\n";
            return;
        }
    }

    auto spot = activeLot->findSpotById(sid);
    if (!spot) {
        cout << "Spot invalid\n";
        return;
    }
    if (spot->isOccupied()) {
        cout << "Spot deja ocupat!\n";
        return;
    }

    shared_ptr<Vehicle> v;
    for (auto& kv : clients) {
        for (auto& vv : kv.second->getVehicles()) {
            if (vv->getId() == vid) {
                v = vv;
                break;
            }
        }
        if (v) break;
    }
    if (!v) {
        cout << "Vehicul necunoscut\n";
        return;
    }

    auto t = make_shared<Ticket>(nextTicketId++, v, spot);
    tickets.push_back(t);
    spot->park(t);
    cout << "Vehicul parcat (Ticket ID=" << t->getId() << ")\n";
}

void ParkingSystem::cmdPay() {
    if (!activeLot) {
        cout << "Selectati o parcare activa!\n";
        return;
    }
    int tid;
    cout << "Ticket ID pentru plata: "; cin >> tid;
    for (auto& t : tickets) {
        if (t->getId() == tid) {
            if (t->isPaid()) {
                cout << "Ticket deja platit\n";
                return;
            }
            auto p = make_shared<Payment>(nextPayId++, t);
            p->process();
            payments.push_back(p);
            return;
        }
    }
    cout << "Ticket invalid\n";
}

void ParkingSystem::cmdCheckOut() {
    if (!activeLot) {
        cout << "Selectati o parcare activa!\n";
        return;
    }
    int cid;
    cout << "Client ID: "; cin >> cid;
    auto cit = clients.find(cid);
    if (cit == clients.end()) {
        cout << "Client invalid\n";
        return;
    }

    for (auto& t : tickets) {
        if (!t->isCheckedOut() && t->isPaid()) {
            bool belongs = false;
            for (auto& v : cit->second->getVehicles()) {
                if (v->getId() == t->getVehicle()->getId()) {
                    belongs = true;
                    break;
                }
            }
            if (!belongs) continue;

            t->checkOut();
            t->getSpot()->leave();
            cout << "Check-out finalizat (Ticket ID=" << t->getId() << ")\n";
            return;
        }
    }
    cout << "Nu exista un ticket platit si activ pentru acest client.\n";
}

void ParkingSystem::cmdAdminReportActive() {
    if (!activeLot) {
        cout << "Selectati mai intai o parcare activa!\n";
        return;
    }
    auto total = activeLot->getSpots().size();
    auto free  = activeLot->getAvailableSpots().size();
    cout << "=== Raport Admin pentru '" << activeLot->getName() << "' ===\n"
              << "ID: "        << activeLot->getId()              << "\n"
              << "Total locuri: " << total                      << "\n"
              << "Libere: "       << free                       << "\n"
              << "Ocupate: "      << (total - free)             << "\n";
}

void ParkingSystem::cmdAdminReport() {
    cout << "=== Raport Admin Global ===\n"
              << "Clienti: "           << clients.size() << "\n"
              << "Parcari: "           << lots.size()    << "\n"
              << "Ticket-uri active: " << tickets.size() << "\n";
}

void ParkingSystem::cmdGlobalReport() {
    cout << "=== Raport Total ===\n";

    size_t totalVehicles = 0;
    for (auto& kv : clients)
        totalVehicles += kv.second->getVehicles().size();
    cout << "Clienti inregistrati: "   << clients.size()     << "\n"
              << "Vehicule inregistrate: "  << totalVehicles      << "\n\n";

    size_t grandTotalSpots = 0, grandFreeSpots = 0;
    for (auto& lot : lots) {
        auto spots = lot->getSpots().size();
        auto free  = lot->getAvailableSpots().size();
        cout << "Parcare ID=" << lot->getId()
                  << " \"" << lot->getName() << "\":\n"
                  << "  Total locuri: " << spots
                  << ", Libere: "      << free
                  << ", Ocupate: "     << (spots - free) << "\n\n";
        grandTotalSpots += spots;
        grandFreeSpots  += free;
    }
    cout << "Total locuri in toate parcarile: " 
              << grandTotalSpots << "\n"
              << "Total locuri libere: " 
              << grandFreeSpots  << "\n\n";

    auto activeRes = count_if(reservations.begin(), reservations.end(),
        [](auto& r){ return r->isActive(); });
    cout << "Rezervari active: " << activeRes << "\n";

    auto activeTickets = count_if(tickets.begin(), tickets.end(),
        [](auto& t){ return !t->isCheckedOut(); });
    cout << "Bilete active (in parcare): " << activeTickets << "\n";

    cout << "Tranzactii de plata: " << payments.size() << "\n";
}
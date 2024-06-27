#ifndef HOTEL_MANAGEMENT_SYSTEM_BILLINGSYSTEM_H
#define HOTEL_MANAGEMENT_SYSTEM_BILLINGSYSTEM_H

#include <string>
#include <vector>
#include "Room.h"

using namespace std;

class Bill {
private:
    string guestName;
    int roomNumber;
    int daysStayed;
    double amount;
public:
    Bill(string guestName, int roomNumber, int daysStayed, double amount);

    string getGuestName() const;

    int getRoomNumber() const;

    int getDaysStayed() const;

    double getAmount() const;
};

class BillingSystem {
public:
    vector<Bill> bills;

    static double calculateAmount(const Room& room, int daysStayed);

    void generateBill(const Room& room, int daysStayed);

    void displayBills() const;

    string serialize() const;
};

#endif // HOTEL_MANAGEMENT_SYSTEM_BILLINGSYSTEM_H

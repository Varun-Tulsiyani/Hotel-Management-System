#ifndef HOTEL_MANAGEMENT_SYSTEM_BILLINGSYSTEM_H
#define HOTEL_MANAGEMENT_SYSTEM_BILLINGSYSTEM_H

#include <string>
#include <vector>
#include "Room.h"

class BillingSystem {
private:
    struct Bill {
        std::string guestName;
        int roomNumber;
        int daysStayed;
        double amount;
    };

    std::vector<Bill> bills;

    static double calculateAmount(int roomNumber, int daysStayed);

public:
    void generateBill(const std::string &guestName, int roomNumber, int daysStayed);

    void displayBills() const;

    std::string serialize() const;
};

#endif // HOTEL_MANAGEMENT_SYSTEM_BILLINGSYSTEM_H

#include "BillingSystem.h"
#include <iostream>
#include <utility>

using namespace std;

string Bill::getGuestName() const { return guestName; }

int Bill::getRoomNumber() const { return roomNumber; }

int Bill::getDaysStayed() const { return daysStayed; }

double Bill::getAmount() const { return amount; }

Bill::Bill(string guestName, int roomNumber, int daysStayed, double amount)
        : guestName(move(guestName)), roomNumber(roomNumber), daysStayed(daysStayed), amount(amount) {}

void BillingSystem::generateBill(const Room& room, int daysStayed) {
    double amount = calculateAmount(room, daysStayed);
    Bill newBill = {room.getGuestName(), room.getRoomNumber(), daysStayed, amount};
    bills.push_back(newBill);
    cout << "Bill generated for " << room.getGuestName() << " for room " << room.getRoomNumber() << " for " << daysStayed
              << " days. Amount: $" << amount << endl;
}

void BillingSystem::displayBills() const {
    for (const Bill &bill: bills) {
        cout << "Guest: " << bill.getGuestName() << ", Room: " << bill.getRoomNumber() << ", Days: "
                  << bill.getDaysStayed() << ", Amount: $" << bill.getAmount() << endl;
    }
}

double BillingSystem::calculateAmount(const Room& room, int daysStayed) {
    return room.getPricePerNight() * daysStayed;
}

string BillingSystem::serialize() const {
    string result;
    for (const auto &bill: bills) {
        result += bill.getGuestName() + "," + to_string(bill.getRoomNumber()) + "," +
                  to_string(bill.getDaysStayed()) + "," + to_string(bill.getAmount()) + "\n";
    }
    return result;
}
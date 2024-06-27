#include "BillingSystem.h"
#include <iostream>

void BillingSystem::generateBill(const std::string &guestName, int roomNumber, int daysStayed) {
    double amount = calculateAmount(roomNumber, daysStayed);
    Bill newBill = {guestName, roomNumber, daysStayed, amount};
    bills.push_back(newBill);
    std::cout << "Bill generated for " << guestName << " for room " << roomNumber << " for " << daysStayed
              << " days. Amount: $" << amount << std::endl;
}

void BillingSystem::displayBills() const {
    for (const Bill &bill: bills) {
        std::cout << "Guest: " << bill.guestName << ", Room: " << bill.roomNumber << ", Days: " << bill.daysStayed
                  << ", Amount: $" << bill.amount << std::endl;
    }
}

double BillingSystem::calculateAmount(int roomNumber, int daysStayed) {
    const double ratePerDay = 100.0;
    return ratePerDay * daysStayed;
}

std::string BillingSystem::serialize() const {
    std::string result;
    for (const auto& bill : bills) {
        result += bill.guestName + "," + std::to_string(bill.roomNumber) + "," + std::to_string(bill.daysStayed) + "," + std::to_string(bill.amount) + "\n";
    }
    return result;
}
#ifndef HOTEL_MANAGEMENT_SYSTEM_RESERVATIONSYSTEM_H
#define HOTEL_MANAGEMENT_SYSTEM_RESERVATIONSYSTEM_H

#include "Room.h"
#include "BillingSystem.h"
#include <vector>
#include <string>

using namespace std;

class ReservationSystem {
private:
    static vector<Room> rooms;
    BillingSystem billingSystem;
public:
    static void initializeSystem();

    static void displayHotelDescription();

    static vector<Room> getRooms();

    void checkIn(int roomNumber, const string &guestName, const string &checkInDate);

    static void checkOut(int roomNumber, const string &checkOutDate);

    static void cancelReservation(const string &date);

    static void displayAvailableRooms() ;

    static void displayBookedRooms() ;

    void displayBills() const;

    void saveCurrentStatus(const string &filename) const;

    void loadFromFile(const string &filename);
};

#endif // HOTEL_MANAGEMENT_SYSTEM_RESERVATIONSYSTEM_H

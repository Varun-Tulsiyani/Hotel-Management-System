#include <vector>
#include "Room.h"
#include "BillingSystem.h"

class ReservationSystem {
private:
    static vector<Room> bookedRoomsList;
    static vector<Room> availableRoomsList;
    static vector<Room> rooms;
    vector<Bill> bills;
public:
    ReservationSystem();

    static void initializeSystem();

    static void displayHotelDescription();

    static void checkIn(Room &room, const string &name, const string &checkInDate);

    static void checkOut(Room &room, const string &checkOutDate);

    static void cancelReservation(const string &date);

    static pair<vector<Room>, vector<Room>> getRooms();

    static void viewBillingSystem();

    static void displayBookings();

    static void saveCurrentStatus(
            const BillingSystem &billingSystem,
            const string &filename
    );

    static void updateRoomsFile();

    static void readDatabase();

    void writeDatabase();

    void updateRoomStatus(int roomNumber, bool isAvailable, const string &guestName = "");

    void addBill(const Bill &bill);
};
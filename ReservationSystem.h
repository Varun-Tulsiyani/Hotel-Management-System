#include <vector>
#include "Room.h"
#include "BillingSystem.h"

class ReservationSystem {
public:
    ReservationSystem();

    static void initializeSystem();

    static void displayHotelDescription();

    static void checkIn(
            Room &room, const std::string &name,
            const std::string &checkInDate, const std::string &checkOutDate
    );

    static void checkOut(Room &room);

    static void cancelReservation();

    static std::pair<std::vector<Room>, std::vector<Room>> getRooms();

    static void viewBillingSystem();

    void displayBookings();

    static void saveCurrentStatus(
            const BillingSystem &billingSystem,
            const std::string &filename
    );
};
#include <vector>
#include "Room.h"

class ReservationSystem {
public:
    ReservationSystem();

    static void initializeSystem();

    void displayHotelDescription();

    virtual void checkIn(
            Room &room, const std::string &name,
            const std::string &checkInDate, const std::string &checkOutDate
    );

    virtual void checkOut(Room &room);

    void cancelReservation();

    std::pair<std::vector<Room>, std::vector<Room>> getRooms();

    void viewBillingSystem();

    void displayBookings() const;

    static void saveCurrentStatus();
};
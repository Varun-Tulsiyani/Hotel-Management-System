#include "Hotel.h"

class ReservationSystem {
private:
    Hotel *hotel;

public:
    ReservationSystem(Hotel *h) : hotel(h) {}

    static void initializeSystem();

    void displayHotelDescription();

    void checkIn();

    void checkOut();

    std::pair<std::vector<Room>, std::vector<Room>> getRooms();

    void viewBillingSystem();

    static void saveCurrentStatus();

    // Other features

    // Other features
};
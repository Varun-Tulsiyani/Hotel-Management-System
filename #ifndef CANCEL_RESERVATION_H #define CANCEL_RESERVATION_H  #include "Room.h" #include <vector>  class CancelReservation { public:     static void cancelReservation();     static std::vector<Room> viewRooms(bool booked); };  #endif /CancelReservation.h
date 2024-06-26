#ifndef CANCEL_RESERVATION_H
#define CANCEL_RESERVATION_H

#include "Room.h"
#include <vector>

class CancelReservation {
public:
    static void cancelReservation();
    static std::vector<Room> viewRooms(bool booked);
};

#endif // CANCEL_RESERVATION_H

#ifndef HOTEL_MANAGEMENT_SYSTEM_HOTEL_H
#define HOTEL_MANAGEMENT_SYSTEM_HOTEL_H


#include <string>
#include <vector>
#include "Room.h"

class Hotel {
private:
    static const std::string name;
    static const std::string location;
    std::vector<Room> rooms;
public:
    Hotel();

    static std::string getName();

    static std::string getLocation();

    std::vector<Room> getRooms();

    void displayHotelDescription();
};


#endif //HOTEL_MANAGEMENT_SYSTEM_HOTEL_H

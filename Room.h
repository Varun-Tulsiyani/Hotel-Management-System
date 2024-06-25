#ifndef HOTEL_MANAGEMENT_SYSTEM_ROOM_H
#define HOTEL_MANAGEMENT_SYSTEM_ROOM_H

#include <string>

class Room {
private:
    int roomNumber;
    std::string roomType;
    double pricePerNight;
    bool isAvailable;
    std::string customerName;
    std::string checkInDate;
    std::string checkOutDate;

public:
    Room(int number, std::string type, double price, bool available, std::string occupant);

    int getRoomNumber() const;

    std::string getRoomType() const;

    double getPricePerNight() const;

    bool getIsAvailable() const;

    std::string getCustomerName() const;

    void bookRoom(std::string name, std::string from, std::string to);

    void releaseRoom();
};

#endif //HOTEL_MANAGEMENT_SYSTEM_ROOM_H

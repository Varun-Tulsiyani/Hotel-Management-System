#ifndef HOTEL_MANAGEMENT_SYSTEM_ROOM_H
#define HOTEL_MANAGEMENT_SYSTEM_ROOM_H

#include <string>
#include <iostream>

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

    Room(const Room &room);

    int getRoomNumber() const;

    std::string getRoomType() const;

    double getPricePerNight() const;

    bool getIsAvailable() const;

    std::string getCustomerName() const;

    std::string getCheckInDate() const;

    std::string getCheckOutDate() const;

    void bookRoom(const std::string &name, const std::string &from, const std::string &to);

    void releaseRoom();

    std::string displayRoom();

    std::string serialize() const ;
};

#endif // HOTEL_MANAGEMENT_SYSTEM_ROOM_H

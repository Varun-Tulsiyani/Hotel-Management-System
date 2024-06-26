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

    int getRoomNumber() const;

    std::string getRoomType() const;

    double getPricePerNight() const;

    bool getIsAvailable() const;

    std::string getCustomerName() const;

    std::string getCheckInDate() const;

    std::string getCheckOutDate() const;

    virtual void bookRoom(std::string name, std::string from, std::string to);

    virtual void releaseRoom();
};

#endif //HOTEL_MANAGEMENT_SYSTEM_ROOM_H

class SingleRoom : public Room {
public:
    SingleRoom(int num) : Room(num) {}

    void checkIn(const std::string &checkInDate) override {
        std::cout << "Checking into Single Room..." << std::endl;
        Room::bookRoom(checkInDate);
    }

    void checkOut() override {
        std::cout << "Checking out from Single Room..." << std::endl;
        Room::releaseRoom();
    }
};


class DoubleRoom : public Room {
public:
    DoubleRoom(int num) : Room(num) {}

    void checkIn(const std::string &checkInDate) override {
        std::cout << "Checking into Double Room..." << std::endl;
        Room::bookRoom(checkInDate);
    }

    void checkOut() override {
        std::cout << "Checking out from Double Room..." << std::endl;
        Room::releaseRoom();
    }
};

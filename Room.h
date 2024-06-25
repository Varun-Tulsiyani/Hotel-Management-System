#ifndef HOTEL_MANAGEMENT_SYSTEM_ROOM_H
#define HOTEL_MANAGEMENT_SYSTEM_ROOM_H

#include <string>

class Room {
private:
    int roomNumber;
    std::string roomType;
    double pricePerNight;
    bool isAvailable;
    std::string occupantName;

public:
    Room(int number, std::string type, double price, bool available, std::string occupant);

    int getRoomNumber() const;

    std::string getRoomType() const;

    double getPricePerNight() const;

    bool getIsAvailable() const;

    std::string getOccupantName() const;

    void setOccupantName(const std::string &occupant);

    void setIsAvailable(bool available);
};

#endif //HOTEL_MANAGEMENT_SYSTEM_ROOM_H

#include "Room.h"

Room::Room(int number, std::string type, double price, bool available, std::string occupant)
        : roomNumber(number), roomType(type), pricePerNight(price), isAvailable(available), occupantName(occupant) {}

int Room::getRoomNumber() const {
    return roomNumber;
}

std::string Room::getRoomType() const {
    return roomType;
}

double Room::getPricePerNight() const {
    return pricePerNight;
}

bool Room::getIsAvailable() const {
    return isAvailable;
}

std::string Room::getOccupantName() const {
    return occupantName;
}

void Room::setOccupantName(const std::string& occupant) {
    occupantName = occupant;
}

void Room::setIsAvailable(bool available) {
    isAvailable = available;
}

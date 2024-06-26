#include "Room.h"

Room::Room(int number, std::string type, double price, bool available, std::string occupant)
        : roomNumber(number), roomType(type), pricePerNight(price), isAvailable(available), customerName(occupant) {}

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

std::string Room::getCustomerName() const {
    return customerName;
}

std::string Room::getCheckInDate() const {
    return checkInDate;
}

std::string Room::getCheckOutDate() const {
    return checkOutDate;
}

void Room::bookRoom(std::string name, std::string from, std::string to) {
    this->customerName = name;
    this->checkInDate = from;
    this->checkOutDate = to;
    this->isAvailable = false;
}

void Room::releaseRoom() {
    this->customerName = "";
    this->checkInDate = "";
    this->checkOutDate = "";
    this->isAvailable = true;
}

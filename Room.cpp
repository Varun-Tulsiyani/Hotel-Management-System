#include "Room.h"

#include <utility>

Room::Room(int number, std::string type, double price, bool available, std::string occupant)
        : roomNumber(number), roomType(std::move(type)), pricePerNight(price), isAvailable(available),
          customerName(std::move(occupant)) {}

Room::Room(const Room &room)
        : roomNumber(room.roomNumber), roomType(room.roomType), pricePerNight(room.pricePerNight),
          isAvailable(room.isAvailable), customerName(room.customerName) {}

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

void Room::bookRoom(const std::string &name, const std::string &from, const std::string &to) {
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

std::string Room::displayRoom() {
    return "Room Number: " + std::to_string(roomNumber) + ", Room Type: " + roomType
           + ", Price Per Night: " + std::to_string(pricePerNight) + ", Availability: "
           + (isAvailable ? "Available" : "Booked") + ", Customer Name: " + customerName;
}

std::string Room::serialize() const {
    return std::to_string(roomNumber) + "," + roomType + "," + std::to_string(pricePerNight) + "," +
           (isAvailable ? "1" : "0") + "," + customerName;
}
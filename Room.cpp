#include "Room.h"
#include <utility>

using namespace std;

Room::Room() = default;

Room::Room(int number, string type, double price, bool available, string guest)
        : roomNumber(number), roomType(move(type)), pricePerNight(price), isAvailable(available),
          guestName(move(guest)) {}

Room::Room(const Room &room)
        : roomNumber(room.roomNumber), roomType(room.roomType), pricePerNight(room.pricePerNight),
          isAvailable(room.isAvailable), guestName(room.guestName) {}

int Room::getRoomNumber() const {
    return roomNumber;
}

string Room::getRoomType() const {
    return roomType;
}

double Room::getPricePerNight() const {
    return pricePerNight;
}

bool Room::getIsAvailable() const {
    return isAvailable;
}

void Room::setAvailable(bool available) {
    this->isAvailable = available;
}

string Room::getGuestName() const {
    return guestName;
}

void Room::setGuestName(string guestName) {
    this->guestName = move(guestName);
}

string Room::getCheckInDate() const {
    return checkInDate;
}

string Room::getCheckOutDate() const {
    return checkOutDate;
}

void Room::bookRoom(const string &name, const string &from) {
    this->guestName = name;
    this->checkInDate = from;
    this->isAvailable = false;
}

void Room::releaseRoom(const string &to) {
    this->guestName = "";
    this->checkInDate = "";
    this->checkOutDate = to;
    this->isAvailable = true;
}

string Room::displayRoom() {
    return "Room Number: " + to_string(roomNumber) + ", Room Type: " + roomType
           + ", Price Per Night: " + to_string(pricePerNight) + ", Availability: "
           + (isAvailable ? "Available" : "Booked") + ", Guest Name: " + guestName;
}

string Room::serialize() const {
    return to_string(roomNumber) + "," + roomType + "," + to_string(pricePerNight) + "," +
           (isAvailable ? "true" : "false") + "," + guestName;
}
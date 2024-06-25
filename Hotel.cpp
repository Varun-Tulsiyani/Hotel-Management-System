#include <iostream>
#include <iomanip>
#include "Hotel.h"

const std::string Hotel::name = "Hotel Name";
const std::string Hotel::location = "Hotel Location";

Hotel::Hotel() = default;

std::string Hotel::getName() { return Hotel::name; }

std::string Hotel::getLocation() { return Hotel::location; }

std::vector<Room> Hotel::getRooms() { return this->rooms; }

void Hotel::displayHotelDescription() {
    std::cout << "Hotel Name: " << name << std::endl;
    std::cout << "Rooms Information:" << std::endl;
    for (auto &room: rooms) {
        std::cout << "Room " << room.getRoomNumber() << ": " << room.getRoomType() << " at $" << std::fixed
                  << std::setprecision(2) << room.getPricePerNight() << " per night" << std::endl;
    }
}
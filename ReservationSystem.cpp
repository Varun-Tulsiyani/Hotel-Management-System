#include "ReservationSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

ReservationSystem::ReservationSystem() = default;

void ReservationSystem::initializeSystem() {
    std::ifstream inFile("../initialFile.txt");

    if (!inFile) {
        std::cerr << "Error opening file!" << std::endl;
//        return "";
    }

    std::string data, line;
    while (std::getline(inFile, line)) {
        data += line + "\n";
    }

//    return data;
}

void ReservationSystem::displayHotelDescription() {
    std::string hotelName = "Hotel Name";
    std::string hotelLocation = "Hotel Location";

    std::cout << "Hotel Name: " << hotelName << std::endl;
    std::cout << "Hotel Location: " << hotelLocation << std::endl;
    std::cout << "Rooms Information:" << std::endl;
    for (auto &room: rooms) {
        std::cout << "Room " << room.getRoomNumber() << ": " << room.getRoomType() << " at $" << std::fixed
                  << std::setprecision(2) << room.getPricePerNight() << " per night" << std::endl;
    }
}

void ReservationSystem::checkIn(
        Room &room, const std::string &name,
        const std::string &checkInDate, const std::string &checkOutDate
) {
    if (!room.getIsAvailable()) {
        throw std::runtime_error("Room already booked.");
    }
    room.bookRoom(name, checkInDate, checkOutDate);
    std::cout << "Checked in to room " << room.getRoomNumber() << " from " << checkInDate << " to " << checkOutDate
              << std::endl;
}

void ReservationSystem::checkOut(Room &room) {
    if (room.getIsAvailable()) {
        throw std::runtime_error("Room is not booked.");
    }
    room.releaseRoom();
    std::cout << "Checked out from room " << room.getRoomNumber() << std::endl;
}

void ReservationSystem::cancelReservation() {
    auto rooms = getRooms();
    auto &bookedRooms = rooms.first;

    if (bookedRooms.empty()) {
        std::cout << "No booked rooms to cancel." << std::endl;
        return;
    }

    std::cout << "Booked Rooms:" << std::endl;
    for (const auto &room: bookedRooms) {
        std::cout << "Room Number: " << room.getRoomNumber() << ", Type: " << room.getRoomType()
                  << ", Customer Name: " << room.getCustomerName() << std::endl;
    }

    int roomNumber;
    std::cout << "Enter room number to cancel reservation: ";
    std::cin >> roomNumber;

    for (auto &room: bookedRooms) {
        if (room.getRoomNumber() == roomNumber) {
            room.releaseRoom();
            break;
        }
    }


    std::ofstream outFile("../room.txt");
    for (const auto &room: rooms.first) {
        outFile << room.getRoomNumber() << ',' << room.getRoomType() << ',' << room.getPricePerNight() << ','
                << room.getIsAvailable() << ',' << room.getCustomerName() << ',' << room.getCheckInDate() << ','
                << room.getCheckOutDate() << '\n';
    }
    outFile.close();

    std::cout << "Reservation canceled successfully." << std::endl;
}

std::pair<std::vector<Room>, std::vector<Room>> ReservationSystem::getRooms() {
    std::ifstream inFile("../room.txt");

    if (!inFile) {
        std::cerr << "Error opening file!" << std::endl;
        return {};
    }

    std::string line;
    std::vector<Room> bookedRoomsList;
    std::vector<Room> availableRoomsList;

    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int roomNumber = std::stoi(token);

        std::string roomType;
        std::getline(ss, roomType, ',');

        std::getline(ss, token, ',');
        double pricePerNight = std::stod(token);

        std::getline(ss, token, ',');
        bool isAvailable = (token == "true");

        std::string occupantName;
        std::getline(ss, occupantName, ',');

        isAvailable ? availableRoomsList.emplace_back(roomNumber, roomType, pricePerNight, isAvailable, occupantName)
                    : bookedRoomsList.emplace_back(roomNumber, roomType, pricePerNight, isAvailable, occupantName);
    }

    return {bookedRoomsList, availableRoomsList};
}

void ReservationSystem::displayBookings() const {
    std::cout << "Current bookings:" << std::endl;
    for (const auto &room: rooms) {
        std::cout << "Room " << room->getRoomNumber() << ": "
                  << (room->getIsBooked() ? "Booked" : "Available");
        if (room->getIsBooked()) {
            std::cout << " (Checked in: " << room->getCheckInDateTime() << ")";
        } else if (!room->getCheckOutDateTime().empty()) {
            std::cout << " (Last checked out: " << room->getCheckOutDateTime() << ")";
        }
        std::cout << std::endl;
    }
}

void ReservationSystem::viewBillingSystem() {}

void ReservationSystem::saveCurrentStatus() {
    std::ofstream outFile("../database.txt");

    if (!outFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
}

#include "ReservationSystem.h"
#include "BillingSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
    auto [bookedRoomsList, availableRoomsList] = getRooms();
    auto &bookedRooms = bookedRoomsList;

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
    for (const auto &room: bookedRoomsList) {
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

void ReservationSystem::displayBookings() {
    std::cout << "Current bookings:" << std::endl;
    auto [bookedRoomsList, availableRoomsList] = getRooms();
    for (const auto &room: bookedRoomsList) {
        std::cout << "Room " << room.getRoomNumber() << ": "
                  << (room.getIsAvailable() ? "Booked" : "Available");
        if (room.getIsAvailable()) {
            std::cout << " (Checked in: " << room.getCheckInDate() << ")";
        } else if (!room.getCheckOutDate().empty()) {
            std::cout << " (Last checked out: " << room.getCheckOutDate() << ")";
        }
        std::cout << std::endl;
    }
}

void ReservationSystem::viewBillingSystem() {}

void ReservationSystem::saveCurrentStatus(
        const BillingSystem &billingSystem,
        const std::string &filename
) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for saving state: " << filename << std::endl;
        return;
    }

    // Serialize rooms
    file << "Rooms:\n";

    auto [bookedRoomsList, availableRoomsList] = getRooms();
    std::vector<Room> rooms;
    rooms.reserve(bookedRoomsList.size() + availableRoomsList.size());

    std::string result;
    for (const auto &room: rooms) {
        result += room.serialize() + "\n";
    }

    file << result;

    // Serialize bills
    file << "\nBills:\n";
    file << billingSystem.serialize();

    file.close();
    std::cout << "Current state saved to " << filename << std::endl;
}

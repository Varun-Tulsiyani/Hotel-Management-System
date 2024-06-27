#include "ReservationSystem.h"
#include "BillingSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<Room> ReservationSystem::rooms = getRooms();

void ReservationSystem::initializeSystem() {
    ifstream inFile("../initialFile.txt");

    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string data, line;
    while (getline(inFile, line)) {
        data += line + "\n";
    }

//    return data;
}

void ReservationSystem::displayHotelDescription() {
    string hotelName = "Hotel Name";
    string hotelLocation = "Dubai, United Arab Emirates";

    cout << "Hotel Name: " << hotelName << endl;
    cout << "Hotel Location: " << hotelLocation << endl;
}

void ReservationSystem::checkIn(int roomNumber, const string &guestName, const string &checkInDate) {
    for (auto &room: rooms) {
        if (room.getRoomNumber() == roomNumber && room.getIsAvailable()) {
            room.bookRoom(guestName, checkInDate);
            billingSystem.generateBill(room, 1); // Example: Assume 1 day for initial booking
            return;
        }
    }
    std::cerr << "Room not available for booking.\n";
}

void ReservationSystem::checkOut(int roomNumber, const std::string &checkOutDate) {
    for (auto &room: rooms) {
        if (room.getRoomNumber() == roomNumber && !room.getIsAvailable()) {
            room.releaseRoom(checkOutDate);
            return;
        }
    }
    std::cerr << "Room not currently booked.\n";
}

void ReservationSystem::cancelReservation(const string &date) {
    cout << "Booked Rooms:" << endl;
    displayBookedRooms();

    int roomNumber;
    cout << "Enter room number to cancel reservation: ";
    cin >> roomNumber;

    for (auto &room: rooms) {
        if (room.getRoomNumber() == roomNumber) {
            room.releaseRoom(date);
            break;
        }
    }

    cout << "Reservation canceled successfully." << endl;
}

vector<Room> ReservationSystem::getRooms() {
    ifstream inFile("../room.txt");

    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return {};
    }

    string line;

    while (getline(inFile, line)) {
        istringstream ss(line);
        string token;

        getline(ss, token, ',');
        int roomNumber = stoi(token);

        string roomType;
        getline(ss, roomType, ',');

        getline(ss, token, ',');
        double pricePerNight = stod(token);

        getline(ss, token, ',');
        bool isAvailable = (token == "true");

        string guestName;
        getline(ss, guestName, ',');

        rooms.emplace_back(roomNumber, roomType, pricePerNight, isAvailable, guestName);
    }
    return rooms;
}

void ReservationSystem::displayAvailableRooms() {
    for (const auto &room: rooms) {
        if (room.getIsAvailable()) {
            std::cout << room.displayRoom() << std::endl;
        }
    }
}

void ReservationSystem::displayBookedRooms() {
    for (const auto &room: rooms) {
        if (!room.getIsAvailable()) {
            std::cout << room.displayRoom() << std::endl;
        }
    }
}

void ReservationSystem::displayBills() const {
    billingSystem.displayBills();
}

void ReservationSystem::saveCurrentStatus(const string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    // Serialize rooms
    for (const auto &room: rooms) {
        file << room.serialize() << std::endl;
    }

    // Serialize bills
    file << "BILLS" << std::endl;
    file << billingSystem.serialize();

    file.close();
}

void ReservationSystem::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }

    rooms.clear();
    billingSystem.clearBills();
    std::string line;
    bool readingBills = false;

    while (std::getline(file, line)) {
        if (line == "BILLS") {
            readingBills = true;
            continue;
        }

        if (!readingBills) {
            std::istringstream ss(line);
            int roomNumber;
            std::string roomType;
            double pricePerNight;
            bool isAvailable;
            std::string guestName;

            std::getline(ss, line, ',');
            roomNumber = std::stoi(line);
            std::getline(ss, roomType, ',');
            std::getline(ss, line, ',');
            pricePerNight = std::stod(line);
            std::getline(ss, line, ',');
            isAvailable = line == "true";
            std::getline(ss, guestName, ',');

            Room room(roomNumber, roomType, pricePerNight, isAvailable, guestName);
            rooms.push_back(room);
        } else {
            std::istringstream ss(line);
            std::string guestName;
            int roomNumber;
            int daysStayed;
            double amount;

            std::getline(ss, guestName, ',');
            std::getline(ss, line, ',');
            roomNumber = std::stoi(line);
            std::getline(ss, line, ',');
            daysStayed = std::stoi(line);
            std::getline(ss, line, ',');
            amount = std::stod(line);

            billingSystem.addBill(Bill(guestName, roomNumber, daysStayed, amount));
        }
    }

    file.close();
}

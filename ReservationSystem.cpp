#include "ReservationSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

void ReservationSystem::displayHotelDescription() {}

void ReservationSystem::checkIn() {}

void ReservationSystem::checkOut() {}

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

void ReservationSystem::viewBillingSystem() {}

void ReservationSystem::saveCurrentStatus() {
    std::ofstream outFile("../database.txt");

    if (!outFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
}

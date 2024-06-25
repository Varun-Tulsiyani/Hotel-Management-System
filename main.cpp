#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include "Room.h"
#include "HotelManagementSystem.h" // Uncommented this as it seems necessary
#include "Hotel.h" // Uncommented this as it seems necessary

void displayMenu() {
    std::cout << "1. Check-in Customer" << std::endl;
    std::cout << "2. Check-out Customer" << std::endl;
    std::cout << "3. View Available Rooms" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

std::string readFromInitialFile() {
    std::ifstream inFile("../initialFile.txt");

    if (!inFile) {
        std::cerr << "Error opening file!" << std::endl;
        return "";
    }

    std::string data, line;
    while (std::getline(inFile, line)) {
        data += line + "\n";
    }

    return data;
}

void saveCurrentState(const std::string &data) {
    std::ofstream outFile("../database.txt");

    if (!outFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    outFile << data;
}

std::vector<Room> viewRooms(bool booked) {
    std::ifstream inFile("../room.txt");

    if (!inFile) {
        std::cerr << "Error opening file!" << std::endl;
        return {};
    }

    std::string line;
    std::vector<Room> roomList;
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

        if (isAvailable != booked) {
            roomList.emplace_back(roomNumber, roomType, pricePerNight, isAvailable, occupantName);
        }
    }

    return roomList;
}

void checkInCustomer() {
    // Implement the check-in process
    std::vector<Room> availableRooms = viewRooms(false);

    if (availableRooms.empty()) {
        std::cout << "No available rooms." << std::endl;
        return;
    }

    std::cout << "Available Rooms:" << std::endl;
    for (const auto &room : availableRooms) {
        std::cout << "Room Number: " << room.getRoomNumber() << ", Type: " << room.getRoomType()
                  << ", Price Per Night: " << room.getPricePerNight() << std::endl;
    }

    int roomNumber;
    std::string occupantName;
    std::cout << "Enter room number to book: ";
    std::cin >> roomNumber;
    std::cout << "Enter occupant name: ";
    std::cin.ignore();
    std::getline(std::cin, occupantName);

    std::ifstream inFile("../room.txt");
    std::ofstream outFile("../room_temp.txt");

    if (!inFile || !outFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int fileRoomNumber = std::stoi(token);

        std::string roomType;
        std::getline(ss, roomType, ',');

        std::getline(ss, token, ',');
        double pricePerNight = std::stod(token);

        std::getline(ss, token, ',');
        bool isAvailable = (token == "true");

        std::string fileOccupantName;
        std::getline(ss, fileOccupantName, ',');

        if (fileRoomNumber == roomNumber && isAvailable) {
            isAvailable = false;
            fileOccupantName = occupantName;
        }

        outFile << fileRoomNumber << ',' << roomType << ',' << pricePerNight << ',' << std::boolalpha << isAvailable << ',' << fileOccupantName << '\n';
    }

    inFile.close();
    outFile.close();
    std::remove("../room.txt");
    std::rename("../room_temp.txt", "../room.txt");

    std::cout << "Customer checked in successfully." << std::endl;
}

void checkOutCustomer() {
    // Implement the check-out process
    std::vector<Room> bookedRooms = viewRooms(true);

    if (bookedRooms.empty()) {
        std::cout << "No booked rooms." << std::endl;
        return;
    }

    std::cout << "Booked Rooms:" << std::endl;
    for (const auto &room : bookedRooms) {
        std::cout << "Room Number: " << room.getRoomNumber() << ", Type: " << room.getRoomType()
                  << ", Occupant Name: " << room.getOccupantName() << std::endl;
    }

    int roomNumber;
    std::cout << "Enter room number to check out: ";
    std::cin >> roomNumber;

    std::ifstream inFile("../room.txt");
    std::ofstream outFile("../room_temp.txt");

    if (!inFile || !outFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int fileRoomNumber = std::stoi(token);

        std::string roomType;
        std::getline(ss, roomType, ',');

        std::getline(ss, token, ',');
        double pricePerNight = std::stod(token);

        std::getline(ss, token, ',');
        bool isAvailable = (token == "true");

        std::string fileOccupantName;
        std::getline(ss, fileOccupantName, ',');

        if (fileRoomNumber == roomNumber && !isAvailable) {
            isAvailable = true;
            fileOccupantName = "";
        }

        outFile << fileRoomNumber << ',' << roomType << ',' << pricePerNight << ',' << std::boolalpha << isAvailable << ',' << fileOccupantName << '\n';
    }

    inFile.close();
    outFile.close();
    std::remove("../room.txt");
    std::rename("../room_temp.txt", "../room.txt");

    std::cout << "Customer checked out successfully." << std::endl;
}

int main() {
    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                checkInCustomer();
                break;
            case 2:
                checkOutCustomer();
                break;
            case 3:
            {
                std::vector<Room> availableRooms = viewRooms(false);
                std::cout << "Available Rooms:" << std::endl;
                for (const auto &room : availableRooms) {
                    std::cout << "Room Number: " << room.getRoomNumber() << ", Type: " << room.getRoomType()
                              << ", Price Per Night: " << room.getPricePerNight() << std::endl;
                }
            }
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 4);

    return 0;
}

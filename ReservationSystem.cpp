#include "ReservationSystem.h"
#include "BillingSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<Room> ReservationSystem::bookedRoomsList;
vector<Room> ReservationSystem::availableRoomsList;
vector<Room> ReservationSystem::rooms;


ReservationSystem::ReservationSystem() = default;

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

void ReservationSystem::updateRoomsFile() {
    ofstream outFile("../room.txt", ios::trunc);

    if (!outFile) {
        cerr << "Error opening room.txt for writing!" << endl;
        return;
    }

    for (const auto &room: rooms) {
        outFile << room.getRoomNumber() << "," << room.getRoomType() << ","
                << room.getPricePerNight() << "," << (room.getIsAvailable() ? "Available" : "Occupied") << ","
                << room.getGuestName() << "\n";
    }

    outFile.close();
}

void ReservationSystem::checkIn(Room &room, const string &name, const string &date) {
    if (!room.getIsAvailable()) {
        throw runtime_error("Room already booked.");
    }
    room.bookRoom(name, date);
    cout << "Checked in to room " << room.getRoomNumber() << " from " << date << endl;

    updateRoomsFile();
}

void ReservationSystem::checkOut(Room &room, const string &date) {
    if (room.getIsAvailable()) {
        throw runtime_error("Room is not booked.");
    }
    room.releaseRoom(date);
    cout << "Checked out from room " << room.getRoomNumber() << " on " << date << endl;

    updateRoomsFile();
}

void ReservationSystem::cancelReservation(const string &date) {
    auto &bookedRooms = bookedRoomsList;

    if (bookedRooms.empty()) {
        cout << "No booked rooms to cancel." << endl;
        return;
    }

    cout << "Booked Rooms:" << endl;
    for (const auto &room: bookedRooms) {
        cout << "Room Number: " << room.getRoomNumber() << ", Type: " << room.getRoomType()
                  << ", Guest Name: " << room.getGuestName() << endl;
    }

    int roomNumber;
    cout << "Enter room number to cancel reservation: ";
    cin >> roomNumber;

    for (auto &room: bookedRooms) {
        if (room.getRoomNumber() == roomNumber) {
            room.releaseRoom(date);
            break;
        }
    }

    ofstream outFile("../room.txt");

    if (!outFile) {
        cerr << "Error opening file" << endl;
        return;
    }

    for (const auto &room: bookedRoomsList) {
        outFile << room.getRoomNumber() << ',' << room.getRoomType() << ',' << room.getPricePerNight() << ','
                << room.getIsAvailable() << ',' << room.getGuestName() << ',' << room.getCheckInDate() << ','
                << room.getCheckOutDate() << endl;
    }
    outFile.close();

    cout << "Reservation canceled successfully." << endl;
}

pair<vector<Room>, vector<Room>> ReservationSystem::getRooms() {
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

        isAvailable ? availableRoomsList.emplace_back(roomNumber, roomType, pricePerNight, isAvailable, guestName)
                    : bookedRoomsList.emplace_back(roomNumber, roomType, pricePerNight, isAvailable, guestName);
    }

    return {bookedRoomsList, availableRoomsList};
}

void ReservationSystem::displayBookings() {
    cout << "Current bookings:" << endl;

    for (const auto &room: bookedRoomsList) {
        cout << "Room " << room.getRoomNumber() << ": "
                  << (room.getIsAvailable() ? "Booked" : "Available");
        if (room.getIsAvailable()) {
            cout << " (Checked in: " << room.getCheckInDate() << ")";
        } else if (!room.getCheckOutDate().empty()) {
            cout << " (Last checked out: " << room.getCheckOutDate() << ")";
        }
        cout << endl;
    }
}

void ReservationSystem::viewBillingSystem() {}

vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void ReservationSystem::readDatabase() {
    ifstream inFile("../database.txt");

    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    bool readingRooms = false;
    bool readingBills = false;

    while (getline(inFile, line)) {
        if (line == "Rooms:") {
            readingRooms = true;
            readingBills = false;
            continue;
        } else if (line == "Bills:") {
            readingRooms = false;
            readingBills = true;
            continue;
        }

        if (readingRooms) {
            auto tokens = split(line, ',');
            if (tokens.size() >= 4) {
                int roomNumber = stoi(tokens[0]);
                string roomType = tokens[1];
                double price = stod(tokens[2]);
                bool isAvailable = (tokens[3] == "true");
                string guestName = tokens.size() > 4 ? tokens[4] : "";

                rooms.emplace_back(roomNumber, roomType, price, isAvailable, guestName);
            }
        } else if (readingBills) {
            // Implement bill reading if required
        }
    }
}

void ReservationSystem::writeDatabase() {
    ofstream outFile("../database.txt");

    if (!outFile) {
        cerr << "Error opening file" << endl;
        return;
    }

    outFile << "Rooms:\n";
    for (const auto &room: rooms) {
        outFile << room.getRoomNumber() << "," << room.getRoomType() << "," << room.getPricePerNight() << ","
                << (room.getIsAvailable() ? "true" : "false");
        if (!room.getIsAvailable()) {
            outFile << "," << room.getGuestName();
        }
        outFile << "\n";
    }

    outFile << "Bills:\n";
    for (const auto &bill: bills) {
        // Implement bill writing if required
    }
}

void ReservationSystem::updateRoomStatus(int roomNumber, bool isAvailable, const string &guestName) {
    for (auto &room: rooms) {
        if (room.getRoomNumber() == roomNumber) {
            room.setAvailable(isAvailable);
            room.setGuestName(guestName);
            break;
        }
    }
    writeDatabase();
}

void ReservationSystem::addBill(const Bill &bill) {
    bills.push_back(bill);
    writeDatabase();
}

void ReservationSystem::saveCurrentStatus(
        const BillingSystem &billingSystem,
        const string &filename
) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Failed to open file for saving state: " << filename << endl;
        return;
    }

    // Serialize rooms
    outFile << "Rooms:\n";

    rooms.reserve(bookedRoomsList.size() + availableRoomsList.size());

    string result;
    for (const auto &room: rooms) {
        result += room.serialize() + "\n";
    }

    outFile << result;

    // Serialize bills
    outFile << "\nBills:\n";
    outFile << billingSystem.serialize();

    outFile.close();
    cout << "Current state saved to " << filename << endl;
}

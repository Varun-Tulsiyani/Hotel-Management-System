#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "Room.h"
#include "ReservationSystem.h"

using namespace std;

void displayMenu() {
    cout << "1. Check-in Guest" << endl;
    cout << "2. Check-out Guest" << endl;
    cout << "3. Cancel Reservation" << endl;
    cout << "4. View Available Rooms" << endl;
    cout << "5. View Booked Rooms with information" << endl;
    cout << "6. View Billing System" << endl;
    cout << "7. Exit" << endl;
}

string getCurrentDate() {
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    ostringstream dateStream;
    dateStream << (now->tm_year + 1900) << '-'
               << setw(2) << setfill('0') << (now->tm_mon + 1) << '-'
               << setw(2) << setfill('0') << now->tm_mday;

    return dateStream.str();
}

int main() {
    ReservationSystem::initializeSystem();

    ReservationSystem::displayHotelDescription();

    auto [bookedRoomsList, availableRoomsList] = ReservationSystem::getRooms();
    int choice, roomNumber;
    string guestName, date = getCurrentDate();

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Room Number: ";
                cin >> roomNumber;

                cout << "Enter guest name: ";
                cin >> guestName;

                for (auto room = availableRoomsList.begin(); room != availableRoomsList.end(); ++room) {
                    if (room->getRoomNumber() == roomNumber) {
                        ReservationSystem::checkIn(*room, guestName, date);
                        bookedRoomsList.push_back(*room);
                        availableRoomsList.erase(room);

                        break;
                    }
                }
            }
                break;
            case 2: {
                cout << "Room Number: ";
                cin >> roomNumber;

                for (auto room = bookedRoomsList.begin(); room != bookedRoomsList.end(); ++room) {
                    if (room->getRoomNumber() == roomNumber) {
                        ReservationSystem::checkOut(*room, date);
                        availableRoomsList.push_back(*room);
                        bookedRoomsList.erase(room);

                        break;
                    }
                }
            }
                break;
            case 3:
                ReservationSystem::cancelReservation(date);
                break;
            case 4:
                for (Room availableRoom: availableRoomsList) {
                    cout << availableRoom.displayRoom() << endl;
                }
                break;
            case 5:
                for (Room bookedRoom: bookedRoomsList) {
                    cout << bookedRoom.displayRoom() << endl;
                }
                break;
            case 6:
                ReservationSystem::viewBillingSystem();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        BillingSystem billingSystem;
        ReservationSystem::saveCurrentStatus(billingSystem, "../database.txt");
    } while (choice != 7);

    return 0;
}

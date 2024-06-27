#include <iostream>
#include <iomanip>
#include <sstream>
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
    ReservationSystem system;

    ReservationSystem::initializeSystem();

    // Load existing state from file
    system.loadFromFile("../system_state.txt");

    ReservationSystem::displayHotelDescription();

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

                system.checkIn(roomNumber, guestName, date);
            }
                break;
            case 2: {
                cout << "Room Number: ";
                cin >> roomNumber;

                ReservationSystem::checkOut(roomNumber, date);
            }
                break;
            case 3:
                ReservationSystem::cancelReservation(date);
                break;
            case 4:
                ReservationSystem::displayAvailableRooms();
                break;
            case 5:
                ReservationSystem::displayBookedRooms();
                break;
            case 6:
                system.displayBills();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        system.saveCurrentStatus("../system_state.txt");
    } while (choice != 7);

    return 0;
}

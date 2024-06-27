#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "Room.h"
#include "ReservationSystem.h"

void displayMenu() {
    std::cout << "1. Check-in Customer" << std::endl;
    std::cout << "2. Check-out Customer" << std::endl;
    std::cout << "3. Cancel Reservation" << std::endl;
    std::cout << "4. View Available Rooms" << std::endl;
    std::cout << "5. View Booked Rooms with information" << std::endl;
    std::cout << "6. View Billing System" << std::endl;
    std::cout << "7. Exit" << std::endl;
}

std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::ostringstream dateStream;
    dateStream << (now->tm_year + 1900) << '-'
               << std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << '-'
               << std::setw(2) << std::setfill('0') << now->tm_mday;

    return dateStream.str();
}

int main() {
    ReservationSystem::initializeSystem();

    ReservationSystem::displayHotelDescription();

    auto [bookedRoomsList, availableRoomsList] = ReservationSystem::getRooms();
    int choice, roomNumber;
    std::string customerName, checkInDate, checkOutDate;

    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cout << "Room Number: ";
        std::cin >> roomNumber;

        switch (choice) {
            case 1: {
                std::cout << "Enter customer name: ";
                std::cin >> customerName;
                checkInDate = getCurrentDate();

                for (auto room = availableRoomsList.begin(); room != availableRoomsList.end(); ++room) {
                    if (room->getRoomNumber() == roomNumber) {
                        ReservationSystem::checkIn(*room, customerName, checkInDate, checkOutDate);
                        bookedRoomsList.push_back(*room);
                        availableRoomsList.erase(room);

                        break;
                    }
                }
            }
                break;
            case 2: {
                checkOutDate = getCurrentDate();
                for (auto room = bookedRoomsList.begin(); room != bookedRoomsList.end(); ++room) {
                    if (room->getRoomNumber() == roomNumber) {
                        ReservationSystem::checkOut(*room);
                        availableRoomsList.push_back(*room);
                        bookedRoomsList.erase(room);

                        break;
                    }
                }
            }
                break;
            case 3:
                ReservationSystem::cancelReservation();
                break;
            case 4:
                for (Room availableRoom: availableRoomsList) {
                    std::cout << availableRoom.displayRoom() << std::endl;
                }
                break;
            case 5:
                for (Room bookedRoom: bookedRoomsList) {
                    std::cout << bookedRoom.displayRoom() << std::endl;
                }
                break;
            case 6:
                ReservationSystem::viewBillingSystem();
                break;
            case 7:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }

        BillingSystem billingSystem;
        ReservationSystem::saveCurrentStatus(billingSystem, "../database.txt");
    } while (choice != 7);

    return 0;
}

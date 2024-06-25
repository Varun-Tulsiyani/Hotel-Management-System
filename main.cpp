#include <iostream>
#include <thread>
#include <chrono>
#include "Room.h"
#include "ReservationSystem.h"
#include "Hotel.h"

void displayMenu() {
    std::cout << "1. Check-in Customer" << std::endl;
    std::cout << "2. Check-out Customer" << std::endl;
    std::cout << "3. View Available Rooms" << std::endl;
    std::cout << "4. View Booked Rooms with information" << std::endl;
    std::cout << "5. View Billing System" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

int main() {
    Hotel hotel;
    ReservationSystem system(&hotel);
    auto [bookedRoomsList, availableRoomsList] = system.getRooms();
    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.checkIn();
                break;
            case 2:
                system.checkOut();
                break;
            case 3:
                for (const Room &availableRoom: availableRoomsList) {
                    std::cout << availableRoom.getRoomNumber() << std::endl;
                }
                break;
            case 4:
                for (const Room &bookedRoom: bookedRoomsList) {
                    std::cout << bookedRoom.getRoomNumber() << std::endl;
                }
                break;
            case 5:
                system.viewBillingSystem();
                break;
            case 6:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 6);

    return 0;
}

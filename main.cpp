#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "Room.h"
#include "ReservationSystem.h"

void displayMenu() {
    std::cout << "1. Check-in Customer" << std::endl;
    std::cout << "2. Check-out Customer" << std::endl;
    std::cout << "3. View Available Rooms" << std::endl;
    std::cout << "4. View Booked Rooms with information" << std::endl;
    std::cout << "5. View Billing System" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

int main() {
    ReservationSystem system;
    system.initializeSystem();

    system.displayHotelDescription();

    auto [bookedRoomsList, availableRoomsList] = system.getRooms();
    int choice, roomNumber;
    std::string customerName, checkInDate, checkOutDate;
    time_t curr_time = time(nullptr);
    char *tm = ctime(&curr_time);

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
                std::cout << "Enter check-in date: ";
                std::cin >> checkInDate;
                std::cout << "Enter check-out date: ";
                std::cin >> checkOutDate;
                for (auto &room: availableRoomsList) {
                    if (room.getRoomNumber() == roomNumber) {
                        system.checkIn(room, customerName, checkInDate, checkOutDate);
                        bookedRoomsList.push_back(room);
                        availableRoomsList.erase(
                                std::remove(availableRoomsList.begin(), availableRoomsList.end(), room),
                                availableRoomsList.end()
                        );
                        return 0;
                    }
                }
                throw std::runtime_error("Room number not found.");
            }
            case 2: {
                for (auto &room: bookedRoomsList) {
                    if (room.getRoomNumber() == roomNumber) {
                        system.checkOut(room);
                        availableRoomsList.push_back(room);
                        bookedRoomsList.erase(std::remove(bookedRoomsList.begin(), bookedRoomsList.end(), room),
                                              bookedRoomsList.end());
                        return 0;
                    }
                }
                throw std::runtime_error("Room number not found.");
            }
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

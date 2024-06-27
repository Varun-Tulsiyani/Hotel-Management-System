#ifndef HOTEL_MANAGEMENT_SYSTEM_ROOM_H
#define HOTEL_MANAGEMENT_SYSTEM_ROOM_H

#include <string>
#include <iostream>

using namespace std;

class Room {
private:
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isAvailable;
    string guestName;

public:
    Room();

    Room(int number, string type, double price, bool available, string guest);

    Room(const Room &room);

    int getRoomNumber() const;

    string getRoomType() const;

    double getPricePerNight() const;

    bool getIsAvailable() const;

    void setAvailable(bool available);

    string getGuestName() const;

    void setGuestName(string guestName);

    void bookRoom(const string &name, const string &from);

    void releaseRoom(const string &to);

    string displayRoom() const;

    string serialize() const;
};

#endif // HOTEL_MANAGEMENT_SYSTEM_ROOM_H

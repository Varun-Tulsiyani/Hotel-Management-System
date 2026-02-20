# Hotel Management System

---

### CSCI251 - Advanced Programming

---

### Overview:

A **console-based Hotel Management System** that lets users manage room reservations, check-ins, check-outs, bill
generation, and view room status. This project showcases basic object-oriented programming, file I/O persistence, and
structuring in C++.

---

### Features:

The system currently supports:

- Load hotel rooms from a file
- Display hotel name and location
- Check-in guests and reserve rooms
- Check-out guests and free rooms
- Cancel reservations
- Show available and booked rooms
- Generate and display bills
- Save state to file between sessions

---

### Tech Stack

- C++
- File I/O
- CMake

---

### Project Structure

```
Hotel-Management-System/
├── CMakeLists.txt
├── main.cpp
├── Room.h/.cpp
├── ReservationSystem.h/.cpp
├── BillingSystem.h/.cpp
├── room.txt
├── initialFile.txt
└── system_state.txt
```

- `Room` — model representing room details
- `ReservationSystem` — core logic for bookings
- `BillingSystem` — handles bill calculations
- Text files store room data and system state

# DS-Team

# Campus Resource Reservation System

## Overview

The Campus Resource Reservation System is a C++ console application designed to manage campus resource bookings, active reservations, and cancellation tracking. Implementing custom data structure including linked lists for active reservations and a stack for cancellation history. 


## Structure
- `src/`: Contains all implementation files (.cpp)
- `cmain.cpp`: Main application entry point and interaction menu
- `ReservationManager.cpp`: Manages active reservations using a linked list
- `CancellationHistory.cpp`: Manages cancelled reservations using a stack structure
- `Reservation.cpp`: Handles reservation details and data fields
- `Resource.cpp`: Handles loading and parsing resource data from files
- ` include/`: Contains all header files (.hpp)
- `Data/`: Contains input data files (.txt files)


- Implemented node management, creation, searching and deleting in function to look at active reservations & through the linked list
- Implemented stack operations like push, pop, and peek to track and undo cancellations and its history.
- Implemented resource loading and system data validation by managing what exact information is needed and available in order for reservation information is valid. 

# DS-Team

# Campus Resource Reservation System

## Overview

The Campus Resource Reservation System is a C++ application designed to manage campus resource bookings, active reservations, and cancellation tracking. Implementing custom data structure including linked lists for active reservations and a stack for cancellation history. 


## Structure
- `src/`: Contains all implementation files (.cpp)
- `main.cpp`: Main application entry point and interaction menu
- `ReservationManager.cpp`: Manages active reservations using a linked list
- `CancellationHistory.cpp`: Manages cancelled reservations using a stack structure
- `Reservation.cpp`: Handles reservation details and data fields
- `Resource.cpp`: Handles loading and parsing resource data from files'
- `WaitingList.cpp`: Handles the Queue operation after going through reservation linked list
- ` include/`: Contains all header files (.hpp)
- `Data/`: Contains input data files (.txt files)
- `Searching Algorithm (linear search)/`: Implements linear search to locate reservations by their ID. Displays the reservation information when a match exists. Also handles searches for reservation ID's that do not exist
- `Sorting Algorithm (Merge Sort)`: We implemented merge sort to organize reservations by date. Allows users to view reservations in chronological order. 
- `Resource Availability`: Displays available campus resources. Tracks reservation activity and resource availability. Updates availability based on reservation creation, cancellation, and waiting list promotion. 
- `System Reports`: Generation reports summarizing reservation system activity. Helps users review the current status of the reservation system. 


- Implemented node management, creation, searching and deleting in function to look at active reservations & through the linked list
- Implemented stack operations like push, pop, and peek to track and undo cancellations and its history.
- Implemented resource loading and system data validation by managing what exact information is needed and available in order for reservation information is valid. 


Github Repository Link: https://github.com/S0ft5igna1/DS-Team.git


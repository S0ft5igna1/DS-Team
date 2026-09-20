// copy of main.cpp with the changes made to it for testing purposes of the ReservationManager and CancellationHistory classes
#include <iostream>
#include <string>
#include "Resource.hpp"

#include "../include/Reservation.hpp" // Include the Reservation class
#include "../include/ReservationManager.hpp" // Include the ReservationManager class
#include "../include/CancellationHistory.hpp" // Include the CancellationHistory class

int main()
{


    auto resources = loadResources("Data/resources.txt");
    std::cout << "All Resources:" << std::endl;
    displayResources(resources);
    std::cout << "\nAvailable Resources:" << std::endl;
    displayAvailableResources(resources);
    //return 0;

    
    ReservationManager reservationManager; // Create an instance of ReservationManager
    CancellationHistory cancellationHistory; // Create an instance of CancellationHistory

    int choice;

    // Main menu loop
    do 
    {
        std::cout << "\n";
        std::cout << "===== Campus Resource Reservation System =====\n";
        std::cout << "1. Create Reservation\n";
        std::cout << "2. Cancel Reservation\n";
        std::cout << "3. View Active Reservations\n";
        std::cout << "4. Search Reservation\n";
        std::cout << "5. Undo Cancellation\n";
        std::cout << "6. View Cancellation History\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter Choice: ";

        std::cin >> choice;
        std::cin.ignore(); 

        if (choice == 1)// Create Reservation
        {
            std::string reservationID;
            std::string studentID;
            std::string studentName;
            std::string resourceID;
            std::string date;

            std::cout << "Reservation ID: ";
            std::getline(std::cin, reservationID);

            std::cout << "Student ID: ";
            std::getline(std::cin, studentID);

            std::cout << "Student Name: ";
            std::getline(std::cin, studentName);

            std::cout << "Resource ID: ";
            std::getline(std::cin, resourceID);

            std::cout << "Reservation Date: ";
            std::getline(std::cin, date);

            Reservation reservation(
                reservationID,
                studentID,
                studentName,
                resourceID,
                date
            );

            reservationManager.createReservation(
                reservation
            );
        }

        else if (choice == 2) // Cancel Reservation
        {
            std::string reservationID;

            std::cout << "Enter Reservation ID: ";
            std::getline(std::cin, reservationID);

            reservationManager.cancelReservation(
                reservationID,
                cancellationHistory
            );
        }

        else if (choice == 3) // View Active Reservations
        {
            reservationManager.displayReservations();
        }

        else if (choice == 4) // Search Reservation
        {
            std::string reservationID;
            Reservation reservation;

            std::cout << "Enter Reservation ID: ";
            std::getline(std::cin, reservationID);

            if (reservationManager.searchReservation(
                reservationID,
                reservation))
            {
                std::cout << "\nReservation Found:\n";
                reservation.display();
            }
            else
            {
                std::cout << "Reservation not found.\n";
            }
        }

        else if (choice == 5) // Undo Cancellation
        {
            reservationManager.undoCancellation(
                cancellationHistory
            );
        }

        else if (choice == 6) // View Cancellation History
        {
            cancellationHistory.displayHistory();
        }

        else if (choice == 7) // Exit
        {
            std::cout << "Exiting program.\n";
        }

        else
        {
            std::cout << "Invalid selection.\n";
        }

    } while (choice != 7);

    return 0;
}

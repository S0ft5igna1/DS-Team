// copy of main.cpp with the changes made to it for testing purposes of the ReservationManager and CancellationHistory classes
#include <iostream>
#include <string>
#include <vector>
#include <limits> //for std::numeric_limits

#include "Resource.hpp"
#include "Reservation.hpp" // Include the Reservation class
#include "ReservationManager.hpp" // Include the ReservationManager class
#include "CancellationHistory.hpp" // Include the CancellationHistory class
#include "WaitingList.hpp" // Include the WaitingList class

int main()
{
// Old way of opening was changed to use the loadResources function to load resources from a file
/*
    auto resources = loadResources("Data/resources.txt");
    std::cout << "All Resources:" << std::endl;
    displayResources(resources);
    std::cout << "\nAvailable Resources:" << std::endl;
    displayAvailableResources(resources);
    return 0; 
    */

    //load resources from file
    std::vector<Resource> resources = loadResources("Data/resources.txt");

    // Create the reservation system and cancellation history
    ReservationManager reservationManager; // Create an instance of ReservationManager
    CancellationHistory cancellationHistory; // Create an instance of CancellationHistory
    WaitingList waitingList; // Create an instance of WaitingList


    

    int choice =0; 

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
        std::cout << "7. View Waiting List\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter Choice: ";

    
        //protect against invalid input

        if (!(std::cin >> choice))
        {
            std::cin.clear(); // Clear the error state of std::cin
            
        
            // Ignore the rest of the line to discard invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


            std::cout<< "Invalid input.\n";
            continue;
        }

        //// Ignore the rest of the line to discard any extra input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 



        if (choice == 1)// Create Reservation
        {
            std::string reservationID;
            std::string studentID;
            std::string studentName;
            std::string resourceID;
            std::string date;

            std::cout << "Available Resources:\n";
            displayAvailableResources(resources);

            std::cout << "Reservation ID: ";
            std::getline(std::cin, reservationID);


            std::cout << "Student ID: ";
            std::getline(std::cin, studentID);

            std::cout << "Student Name: ";
            std::getline(std::cin, studentName);

            std::cout << "Resource ID: ";
            std::getline(std::cin, resourceID);

            // Check if the resource exists and is available
            if (!resourceExists(resources, resourceID))
            {
                std::cout << "Error: Resource ID does not exist.\n";
                continue;
            }

            // Check general resource availability
            if (!resourceIsAvailable(resources, resourceID))
            {
                std::cout << "Error: Resource is Unavailable.\n";
                continue;
            }

            std::cout << "Reservation Date: ";
            std::getline(std::cin, date);
            
            // Check for empty reservation information
            if (
                reservationID.empty() ||
                studentID.empty() ||
                studentName.empty() ||
                resourceID.empty() ||
                date.empty()
                )
            {
                std::cout << "Error: Reservation information cannot be empty.\n";
                continue;
            
            }

            // Check for duplicate reservation ID first
            if (reservationManager.reservationExists(reservationID) 
            || waitingList.reservationExists(reservationID))
            {
                std::cout << "Error: Reservation ID already exists.\n";
                continue;
            }


            Reservation reservation(
                reservationID,
                studentID,
                studentName,
                resourceID,
                date
            );

            // Try to create the reservation
            bool created = reservationManager.createReservation(reservation);

            //if the reservation could not be created then its already reserved on the same date
            if (!created)
            {   
                int waitChoice;
                
                std::cout << "Would you like to be added to the waiting list?\n";
                std::cout <<"1. Yes\n";
                std::cout <<"2. No\n";
                std::cout <<"Enter your choice: ";

                std::cin >> waitChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (waitChoice == 1)
                {
                    waitingList.enqueue(reservation);
                }
                else
                {
                    std::cout << "Reservation not created and not added to waiting list.\n";
                }

                
            }

        }

        else if (choice == 2) // Cancel Reservation
        {
            std::string reservationID;

            std::cout << "Enter Reservation ID: ";
            std::getline(std::cin, reservationID);

            // Save the reservation before removing it
            Reservation cancelledReservation;


            if (!reservationManager.searchReservation(reservationID,cancelledReservation))
            {
            std::cout << "Reservation not found.\n";
            continue;
            }

    bool cancelled =
        reservationManager.cancelReservation(
            reservationID,
            cancellationHistory
        );

    // If cancellation worked, check the waiting list
    if (cancelled)
    {
        Reservation waitingReservation;

        bool studentWaiting =
            waitingList.dequeue(
                cancelledReservation.getResourceID(),
                cancelledReservation.getReservationDate(),
                waitingReservation
            );

        // Move first matching student into active reservations
        if (studentWaiting)
        {
            std::cout
                << "Student found on waiting list.\n";

            bool created =reservationManager.createReservation(waitingReservation );

            if (created)
            {
                std::cout
                    << "Waiting-list reservation is now active.\n";
            }
            else
            {
                // Put them back if creation unexpectedly fails
                waitingList.enqueue(waitingReservation);
            }
        }
    }

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

        else if (choice == 7) // View Waiting List
        {
            waitingList.displayWaitingList();
        }

        else if (choice == 8) // Exit
        {
            std::cout << "Exiting program.\n";
        }

        else
        {
            std::cout << "Invalid selection.\n";
        }

    } while (choice != 8);

    return 0;
}

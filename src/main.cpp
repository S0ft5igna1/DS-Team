#include <iostream>
#include <string>
#include "../include/ReservationManager.hpp"

void displayMenuMenu()
{
    std::cout << "  Campus Resource Reservation System  \n";
    std::cout << "======================================\n";
    std::cout << "1. Search Resource By ID ( using Binary Search)\n";
    std::cout << "2. Search Reservations by Student ID ( using Linear Search)\n";
    std::cout << "3. Sort Resources by Name ( using Quick Sort)\n";
    std::cout << "4. Sort Resources by Popularity (using Quick Sort)\n";
    std::cout << "5. Report: Active Reservations\n";
    std::cout << "6. Report: Resource Utilization\n";
    std::cout << "7. Report: Most Requested Resources\n";
    std::cout << "8. Report: Waiting-List Statistics\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter Choice: ";
}

int main()
{
    ReservationManager manager;

    // Load in data from text files 
    manager.loadResourcesFromFile("Data/resource.txt");
    manager.loadReservationsFromFile("Data/reservations/txt");

    int choice = 0;
    while (choice != 9)
    {
        displayMenu();
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch(choice)
        {
            case 1:
            {
                std::string id;
                std::cout << "Enter Resource ID: ";
                std::cin >> id;
                Resource* res = manager.searchResourceByIdBinary(id);
                if (res!= nullptr)
                {
                    std::cout << "Resource Found: ID = " << res->getId()
                              << ", Name=" << res->getName() << "\n";
                }else
                {
                    std::cout << "Resource with ID " << id << " not found.\n";
                }
                break;
            }
            case 2:
            {
                std::string studentId;
                std::cout << "Enter Student ID: ";
                std::cin >> studentId;
                std::vector<Reservation> results = manager.searchReservationsByStudentLinear(studentId);
                if (results.empty())
                {
                    std::cout << "No reservations found for Student ID: " << studentId << "\n"; 
                }else 
                {
                    std::cout << "Found " << results.size() << " reservation(s):\n";
                    for (size_t i = 0; i < results.size(); i++)
                    {
                        std::cout << " -  ID: " << results[i].getId()
                              << ", Resource ID: "<< results[i].getResourceId()
                              <<" , Date: " << results[i].getDate() << "\n";
                    }
                }
                break;
            }
            case 3:
            manager.sortResourcesByName();
            std::cout << :"Resources successfully sorted alphabetically by name.\n";
            break;

            case 4:
            manager.sortResourcesByPopularity();
            std::cout << "Resources successfully sorted by popularity\n";
            break;

            case 5:
            manager.generateActiveReservationsReport();
            break;

            case 6:
            manager.generateResourceUtilizationReport();
            break;

            case 7:
            manager.generateMostRequestedResourcesReport();
            break;

            case 8:
            manager.generateWaitingListStatsReport();
            break;

            case 9:
            std::cout << "Exiting System. Goodbye!\n";
            break;

            default:
            std::cout << "Invalid choice. Please select an option between 1 and 9.\n";
            break;

        }
    }
    return 0;
}
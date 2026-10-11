#include <iostream>
#include "../include/ReservationManager.hpp"

void printMenu() {
    std::cout << "\n====================================\n";
    std::cout << "  Campus Resource Reservation System\n";
    std::cout << "====================================\n";
    std::cout << "1. Search Resource by ID (Binary Search)\n";
    std::cout << "2. Search Reservations by Student ID (Linear Search)\n";
    std::cout << "3. Sort Resources by Name (Quick Sort)\n";
    std::cout << "4. Sort Resources by Popularity (Quick Sort)\n";
    std::cout << "5. Active Reservations Report\n";
    std::cout << "6. Resource Utilization Report\n";
    std::cout << "7. Most Requested Resources Report\n";
    std::cout << "8. Waiting-List Statistics Report\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter choice: ";
}

int main() {
    ReservationManager manager;

    // Load data files on startup
    manager.loadResourcesFromFile("Data/resources.txt");
    manager.loadReservationsFromFile("Data/reservations.txt");

    int userChoice = 0;
    while (userChoice != 9) {
        printMenu();
        if (!(std::cin >> userChoice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (userChoice) {
            case 1: {
                std::string targetId;
                std::cout << "Enter Resource ID: ";
                std::cin >> targetId;
                Resource* res = manager.searchResourceByIdBinary(targetId);
                if (res != nullptr) {
                    res->display();
                } else {
                    std::cout << "No resource found with ID: " << targetId << "\n";
                }
                break;
            }
            case 2: {
                std::string studentId;
                std::cout << "Enter Student ID: ";
                std::cin >> studentId;
                auto results = manager.searchReservationsByStudentLinear(studentId);
                if (results.empty()) {
                    std::cout << "No reservations found for Student ID: " << studentId << "\n";
                } else {
                    std::cout << "Found " << results.size() << " reservation(s):\n";
                    for (const auto& r : results) {
                        std::cout << " - ID: " << r.getId() 
                                  << " | Resource: " << r.getResourceId() 
                                  << " | Date: " << r.getDate() << "\n";
                    }
                }
                break;
            }
            case 3:
                manager.sortResourcesByName();
                std::cout << "Sorted resources by name using Quick Sort.\n";
                break;
            case 4:
                manager.sortResourcesByPopularity();
                std::cout << "Sorted resources by popularity using Quick Sort.\n";
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
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice (1-9).\n";
                break;
        }
    }

    return 0;
}
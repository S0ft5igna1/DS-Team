#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include "Resource.hpp"
#include "Reservation.hpp"
#include "ReservationManager.hpp"
#include "CancellationHistory.hpp"
#include "WaitingList.hpp"
#include "DateValidation.hpp"

// Find data files when run from the project root or a build directory.
static std::string dataPath(const std::string& name)
{
    const std::string paths[] = {"Data/", "../Data/", "../../Data/"};
    for (const std::string& path : paths)
    {
        std::ifstream file(path + name);
        if (file.is_open()) return path + name;
    }
    return "Data/" + name;
}

static int loadReservations(const std::string& filename, ReservationManager& manager,
                            const std::vector<Resource>& resources, WaitingList& waitingList)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open " << filename << "\n";
        return -1;
    }
    int loaded = 0, lineNumber = 0;
    std::string line;
    while (std::getline(file, line))
    {
        ++lineNumber;
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string id, studentID, studentName, resourceID, date;
        if (!std::getline(ss, id, '|') || !std::getline(ss, studentID, '|') ||
            !std::getline(ss, studentName, '|') || !std::getline(ss, resourceID, '|') ||
            !std::getline(ss, date) || id.empty() || studentID.empty() ||
            studentName.empty() || !resourceExists(resources, resourceID) || !isValidDate(date) ||
            manager.reservationExists(id) || waitingList.reservationExists(id))
        {
            std::cerr << "Skipping invalid reservation on line " << lineNumber << ".\n";
            continue;
        }
        Reservation reservation(id, studentID, studentName, resourceID, date);
        // Existing file reservations remain valid even if resource is now administratively unavailable.
        // A same-date collision goes into the queue, preserving the supplied request.
        if (manager.createReservation(reservation)) ++loaded;
        else waitingList.enqueue(reservation);
    }
    return loaded;
}

static void displayDynamicAvailability(const std::vector<Resource>& resources, const ReservationManager& manager)
{
    std::cout << "\n===== Resource Status =====\n";
    for (const Resource& resource : resources)
    {
        std::cout << resource.getId() << " - " << resource.getName()
                  << " | " << (resource.getAvailability() ? "Enabled" : "Administratively unavailable")
                  << " | Active bookings: " << manager.countForResource(resource.getId())
                  << " | Free dates depend on the requested date\n";
    }
}

static void displayReports(const std::vector<Resource>& resources, const ReservationManager& manager,
                           const WaitingList& waitingList)
{
    std::cout << "\n===== System Reports =====\n";
    std::cout << "Active reservations: " << manager.getReservationCount() << "\n";
    manager.displayReservations();
    std::cout << "\n===== Resource Utilization and Waiting List =====\n";
    int highest = 0;
    for (const Resource& resource : resources)
    {
        int active = manager.countForResource(resource.getId());
        int waiting = waitingList.countForResource(resource.getId());
        int requests = active + waiting;
        if (requests > highest) highest = requests;
        std::cout << resource.getId() << " (" << resource.getName() << ")"
                  << " | Active: " << active << " | Waiting: " << waiting
                  << " | Current requests: " << requests << "\n";
    }
    std::cout << "\nTotal students waiting: " << waitingList.getWaitingCount() << "\n";
    std::cout << "\n===== Most Requested Resources =====\n";
    if (highest == 0) std::cout << "No requests yet.\n";
    else for (const Resource& resource : resources)
    {
        int requests = manager.countForResource(resource.getId()) +
                       waitingList.countForResource(resource.getId());
        if (requests == highest)
            std::cout << resource.getId() << " - " << resource.getName()
                      << " (" << requests << " current requests)\n";
    }
}

static std::string readField(const std::string& prompt)
{
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

int main()
{
    std::vector<Resource> resources = loadResources(dataPath("resources.txt"));
    if (resources.empty())
    {
        std::cerr << "No resources loaded. Run from the project directory.\n";
        return 1;
    }
    ReservationManager reservationManager;
    CancellationHistory cancellationHistory;
    WaitingList waitingList;
    int loaded = loadReservations(dataPath("reservations.txt"), reservationManager, resources, waitingList);
    if (loaded < 0) return 1;
    std::cout << "Loaded " << loaded << " active reservations from file.\n";

    while (true)
    {
        std::cout << "\n===== Campus Resource Reservation System =====\n"
                  << "1. Create Reservation\n2. Cancel Reservation\n"
                  << "3. View Active Reservations\n4. Search Reservation (Linear Search)\n"
                  << "5. Undo Cancellation\n6. View Cancellation History\n"
                  << "7. View Waiting List\n8. View Resource Availability\n"
                  << "9. Sort Reservations by Date (Merge Sort)\n"
                  << "10. System Reports\n11. Exit\nEnter Choice: ";
        int choice;
        if (!(std::cin >> choice))
        {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a menu number.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 1)
        {
            displayDynamicAvailability(resources, reservationManager);
            std::string id = readField("Reservation ID: ");
            std::string studentID = readField("Student ID: ");
            std::string name = readField("Student Name: ");
            std::string resourceID = readField("Resource ID: ");
            std::string date = readField("Reservation Date (MM/DD/YYYY): ");
            if (id.empty() || studentID.empty() || name.empty() || resourceID.empty())
            {
                std::cout << "Error: Reservation information cannot be empty.\n";
                continue;
            }
            if (!resourceExists(resources, resourceID))
            {
                std::cout << "Error: Resource ID does not exist.\n";
                continue;
            }
            if (!resourceIsAvailable(resources, resourceID))
            {
                std::cout << "Error: Resource is administratively unavailable.\n";
                continue;
            }
            if (!isValidDate(date))
            {
                std::cout << "Error: Invalid date. Use a real date in MM/DD/YYYY format.\n";
                continue;
            }
            if (reservationManager.reservationExists(id) || waitingList.reservationExists(id))
            {
                std::cout << "Error: Reservation ID already exists.\n";
                continue;
            }
            Reservation reservation(id, studentID, name, resourceID, date);
            if (!reservationManager.createReservation(reservation))
            {
                std::string answer = readField("Add to waiting list? (1=Yes, 2=No): ");
                if (answer == "1") waitingList.enqueue(reservation);
                else std::cout << "Reservation not created.\n";
            }
        }
        else if (choice == 2)
        {
            std::string id = readField("Enter Reservation ID: ");
            Reservation canceled;
            if (!reservationManager.searchReservation(id, canceled))
            {
                std::cout << "Reservation not found.\n";
                continue;
            }
            if (reservationManager.cancelReservation(id, cancellationHistory))
            {
                Reservation promoted;
                if (waitingList.dequeue(canceled.getResourceID(), canceled.getReservationDate(), promoted))
                {
                    if (reservationManager.createReservation(promoted))
                        std::cout << "Waiting-list reservation is now active.\n";
                    else
                    {
                        // Preserve the request if promotion unexpectedly fails.
                        waitingList.enqueue(promoted);
                        std::cout << "Promotion failed; request returned to waiting list.\n";
                    }
                }
            }
        }
        else if (choice == 3) reservationManager.displayReservations();
        else if (choice == 4)
        {
            Reservation found;
            if (reservationManager.searchReservation(readField("Enter Reservation ID: "), found))
            {
                std::cout << "Reservation Found:\n";
                found.display();
            }
            else std::cout << "Reservation not found.\n";
        }
        else if (choice == 5) reservationManager.undoCancellation(cancellationHistory, waitingList);
        else if (choice == 6) cancellationHistory.displayHistory();
        else if (choice == 7) waitingList.displayWaitingList();
        else if (choice == 8) displayDynamicAvailability(resources, reservationManager);
        else if (choice == 9) reservationManager.displaySortedReservations();
        else if (choice == 10) displayReports(resources, reservationManager, waitingList);
        else if (choice == 11)
        {
            std::cout << "Exiting program.\n";
            break;
        }
        else std::cout << "Invalid selection.\n";
    }
    return 0;
}

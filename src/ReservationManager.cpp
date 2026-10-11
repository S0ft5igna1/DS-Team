
#include "../include/ReservationManager.hpp" 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <regex>

ReservationManager::ReservationManager() {}

void ReservationManager::addResource(const Resource& resource)
{
    resources.push_back(resource);
}
void ReservationManager::addReservation(const Reservation& reservation)
{
    if (!isValidDate(reservation.getDate()))
    {
        std::cout << "Error: Invalid date format or date value ("
                  << reservation.getDate() << "). Reservation rejected.\n";
        return;
    }
    reservations.push_back(reservation);
}

bool ReservationManager::undoCancellation(const std::string& reservationId) 
{
    // Check if the student/reservation is currently waiting on the WaitingList queue
    if (waitingList.isStudentInWaitingList(reservationId)) 
    {
        std::cout << "Cannot undo cancellation: Reservation ID " << reservationId 
                  << " is currently active in the waiting list!\n";
        return false;
    }

    // Perform the restore...
    return true;
}

// Quick Sort Implementation ( No std::sort used)

// Sort by Resource Name
int ReservationManager::partitionByName(std::vector<Resource>& resList, int low, int high) // partition helper sorts resources alphabetically 
{
    std::string pivot = resList[high].getName();
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (resList[j].getName() <= pivot)
        {
            i++;
            //swap elements
            Resource temp = resList[i];
            resList[i] = resList[j];
            resList[j] = temp;
        }
    }
    Resource temp = resList[i+1];
    resList[i + 1] = resList[high];
    resList[high] = temp;
    return i + 1;
}

void ReservationManager::quickSortResourcesByName(std::vector<Resource>& resList, int low, int high)
{
    if (low < high)
    {
        int pi = partitionByName(resList, low, high);
        quickSortResourcesByName(resList, low, p - 1);
        quickSortResourcesByName(resList, p + 1, high);
    }
}

void ReservationManager::sortResourcesByName()
{
    if (!resources.empty())
    {
        quickSortResourcesByName(resources, 0, resources.size() - 1);
    }
}

// Sort by Resource ID (Needed before Binary Search (Requires to be sorted))
int ReservationManager::partitionById(std::vector<Resource>& resList, int low, int high)
{
    std::string pivot = resList[high].getId();
    int i = low - 1
    for (int j = low; j < high; j++)
    {
        if (resList[j].getId() <= pivot)
        {
            i++;
            Resource temp = resList[i];
            resList[i] = resList[j];
            resList[j] = temp;
        }
    }
    Resource temp = resList[i + 1];
    resList[i + 1] = resList[high];
    resList[high] = temp;
    return i + 1;
}

void ReservationManager::quickSortResourcesById(std::vector<Resource>& resList, int low, int high )
{
    if (low < high)
    {
        int p = partitionById(resList, low, high);
        quickSortResourcesById(resList, low, p - 1);
        quickSortResourcesById(resList, p + 1, high);
    }
}

void ReservationManager::sortResourcesById()
{
    if (!resources.empty())
    {
        quickSortResourcesById(resources, 0, resources.size() - 1);
    }
}

// Sort by Resource Popularity ( in descending order)
int ReservationManager::partitionByPopularity(std::vector<Resource>& resList, int low, int high)
{
    int pivot = resList[high].getReservationCount();
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (resList[j].getReservationCount() <= pivot)
        {
            i++;
            Resource temp = resList[i];
            resList[i] = resList[j];
            resList[j] = temp;
        }
    }
    Resource temp = resList[i + 1];
    resList[i + 1] = resList[high];
    resList[high] = temp;
    return i + 1;
}

void ReservationManager::quickSortResourcesByPopularity(std::vector<Resource>& resList, int low, int high)
{
    if (low < high)
    {
        int pi = partitionByPopularity(resList, low, high);
        quickSortResourcesByPopularity(resList, low, p - 1);
        quickSortResourcesByPopularity(resList, p + 1, high);
    }
}

void ReservationManager::sortResourcesByPopularity()
{
    if(!resources.empty())
    {
        quickSortResourcesByPopularity(resources, 0, resources.size() - 1);
    }
}

/* Searching Implementations*/ 

//Binary Search for Resource ID ( List must be sorted)

Resource* ReservationManager::searchResourceByIdBinary(const std::string& id)
{
    sortResourcesById(); // makes sure array is sorted by ID prior to running binary search

    int low = 0;
    int high = (int)resources.size() - 1;
    
    while(low <= high)
    {
        int mid = low + (high - low) / 2;
        if (resources[mid].getId() == id)
        {
            return &resources[mid];
        }
        if (resources[mid].getId() < id)
        {
            low = mid + 1;
        }else
        {
            high = mid - 1;
        }
    }
    return nullptr;
}

//Linear Search for Reservations by Student ID/Name

std::vector<Reservation> ReservationManager::searchReservationsByStudentLinear(const std::string& studentId)
{
    std::vector<Reservation> matches;
    for (size_t i = 0; i < reservations.size(); i++)
    {
        if(reservations[i].getStudentId() == studentId)
        {
            matches.push_back(reservations[i]);
        }
    }
    return matches;
}

// Reporting System

void ReservationManager::generateActiveReservationsReport() const
{
    std::cout << "   Active Reservations Report \n";
    std::cout << "----------------------------- \n";
    std::cout << std::left << std::setw(12) << "Res ID"
              << std::setw(15) << "Resource ID"
              << std::setw(15) << "Student ID"
              << std::setw(15) << "Date" << "\n";
    std::cout << " --------------------------------\n";

    int activeCount = 0;
    for (size_t i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].getStatus() == "Active" || reservations[i].getStatus() == "CONFIRMED")
        {
            std::cout << std::left << std::setw(12) << reservations[i].getId()
                      << std::setw(15) << reservations[i].getResourceId()
                      << std::setw(15) << reservations[i].getStudentId()
                      << std::setw(15) << reservations[i].getDate() << "\n";
            activeCount++;
        }
    }
    std::cout << "Total Active Reservations: " << count << "\n";
}

void ReservationManager::generateResourceUtilizationReport() const
{
    std::cout << "       Resource Utilization Report        \n";
    std::cout << "------------------------------------------\n";
    std::cout << std::left << std::setw(12) << "Resource ID"
              << std::setw(20) << "Name"
              << std::setW(15) << "Reservatiosn" << "\n";
    std::cout << "------------------------------------------\n";

    for (size_t i = 0; i < resources.size(); i++)
    {
        std::cout << std::left << std::setw(12) << resources[i].getId()
                  << std:: setw(20) << resources[i].getName()
                  << std:: setw(15) << resources[i].getReservationCount() << "\n";
    }
}

void ReservationManager::generateMostRequestedResourcesReport()
{
    sortResourcesByPopularity(); // sorts resources using Quick Sort before finalizing report

    std::cout << "       Most Requested Resources Report     \n";
    std::cout << "-------------------------------------------\n";
    std::cout << std::left << std::setw(8) << "Rank"
              << std::setw (12) << "Resource ID"
              << std::setw (20) << "Name"
              << std::setw (12) << "Total Uses" << "\n";
    std::cout << "-------------------------------------------\n";

    for (size_t i = 0; i < resources.size(); i++)
    {
        std::cout << std::left << std::setw(8) << (i + 1)
                  << std::setw(12) << resources[i].getId()
                  << std::setw(20) << resources[i].getName()
                  << std::setw(12) << resources[i].getReservationCount() << "\n";
    }
}

void ReservationManager::generateWaitingListStatsReport() const
{
    std::cout << "        Waiting List Statistics           \n";
    std::cout << "------------------------------------------\n";
    std::cout << std::left << std::setw(15) << "Resource ID"
              << std::setw(20) << "Students Waiting" << "\n":
    std::cout << "------------------------------------------\n";

    for (size_t i = 0; i < resources.size(); i++)
    {
        int count = waitingList.getWaitingCountForResource(resources[i].getId());
        std::cout << std::left << std::setw(15) << resources[i].getId()
                  << std::setw(20) << count << "\n";
    }
}

// Helper method to validate YYYY-MM-DD date format and calendar limits
bool isValidDate(const std::string& dateStr) 
{
    // Regex pattern for YYYY-MM-DD
    std::regex datePattern("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$");
    if (!std::regex_match(dateStr, datePattern))
    {
        return false;
    }

    int year, month, day;
    char dash1, dash2;
    std::stringstream ss(dateStr);
    ss >> year >> dash1 >> month >> dash2 >> day;

    // days-in-month validation
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Leap year check
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
    {
        daysInMonth[2] = 29;
    }

    return day <= daysInMonth[month];
}

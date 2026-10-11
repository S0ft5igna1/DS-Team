
#include "../include/ReservationManager.hpp" 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>


ReservationManager::ReservationManager() {}

void ReservationManager::addResource(const Resource& resource)
{
    resources.push_back(resource);
}
void ReservationManager::addReservation(const Reservation& reservation)
{
    reservations.push_back(reservation);
}

// Quick Sort Implementation ( No std::sort used)

// Sort by Resource Name
int ReservationManager::partitionByName(std::vector<Resource>& resList, int low, int high)
{
    std::string pivot = resList[high].getName();
    int i = low - 1;
    for (int j = low; j < high; i++)
    {
        if (resList[j].getName() <= pivot)
        {
            i++;
            std::swap(resList[i], resList[j]);
        }
    }
    std::swap(resList[i+1], resList[high]);
    return i + 1;
}

void ReservationManager::quickSortResourceByName(std::vector<Resource>& resList, int low, int high)
{
    if (low < high)
    {
        int pi = partitionByName(resList, low, high);
        quickSortResourceByName(resList, low, pi -1);
        quickSortResourceByName(resList, pi + 1, high);
    }
}

void ReservationManager::sortResourcesByName()
{
    if (!resources.empty())
    {
        quickSortResourceByName(resources, 0, resources.size() - 1);
    }
}

// Sort by Resource ID (Needed before Binary Search (Requires to be sorted))
int ReservationManager::partitionById(std::vector<Resource>& resList, int low, int high)
{
    std::string pivot = resList[high].getId();
    int i = low -1
    for (int j = low; j < high; ++j)
    {
        if (resList[j].geId() <= pivot)
        {
            i++;
            std::swap(resList[i], resList[j]);
        }
    }
    std::swap(resList[i + 1], resList[high]);
    return i + 1;
}

void ReservationManager::quickSortResourcesById(std::vector<Resource>& resList, int low, int high )
{
    if (low < high)
    {
        int pi = partitionById(resList, low, high);
        quickSortResourcesById(resList, low, pi - 1);
        quickSortResourcesById(resList, pi + 1, high);
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
int ReservationManager::partitionByPopularity(std::vector<Resoruce>& resList, int low, int high)
{
    int pivot = resList[high].getReservationCount();
    int i = low - 1;
    for(int j = low; j < high; ++j)
    {
        if(resList[j].getReservationCount() >= pivot)
        {
            i++;
            std::swap(resList[i], resList[j]);
        }
    }
    std::swap(resList[i + 1], resList[high];
        return i + 1;
}

void ReservationManager::quickSortResourcesByPopularity(std::vector<Resource>& resList, int low, int high)
{
    if (low < high)
    {
        int pi = partitionByPopularity(resList, low, high);
        quickSortResourcesByPopularity(resList, low, pi - 1);
        quickSortResourcesByPopularity(resList, pi + 1, high);
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

//Binary Search for Resource ID ( List must be pre-sorted)

Resource* ReservationManager::searchResourceByIdBinary(const std::string& id)
{
    sortResourcesById();

    int low = 0;
    int high = static_cast<int>(resources.size()) -1;
    
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

std::vector<Reservation> ReservationManager::searchReservationByStudentLinear(const std::string& studentId)
{
    std::vector<Reservation> matches;
    for (size_t i = 0; i < reservations.size(); ++i)
    {
        if(reservations[i].getStudentId() == studentId)
        {
            matches.push_back(reservations[i]);
        }
    }
    return matches;
}

// System Reporting System

void ReservationManager::generateActiveReservationsReport() const
{
    std::cout << "\n ============================= \n";
    std::cout << "      Active Reservations Report \n";
    std::cout << "================================ \n";
    std::cout << std:left << std::setw(12) << "Res ID"
              << std::setw(15) << "Resource ID"
              << std::setw(15) << "Student ID"
              << std::setw(15) << "Date" << "\n";
    std::cout << " --------------------------------\n";

    int count = 0;
    for (size_t i = 0; i < reservations.size(); ++i)
    {
        if (reservations[i].getStatus() == "Active" || reservations[i].getStatus() == "CONFIRMED")
        {
            std::cout << std::left << std::setw(12) << reservations[i].getId()
                      << std::setw(15) << reservations[i].getResourceId()
                      << std::setw(15) << reservations[i].getStudentId()
                      << std::setw(15) << reservations[i].getDate() << "\n";
            count++;
        }
    }
    std::cout << "---------------------------------\n";
    std::cout << "Total Active Reservations: " << count << "\n";
}

void ReservationManager::generateResourceUtilizationReport() const
{
    std::cout << "\n========================================\n";
    std::cout << "       Resource Utilization Report        \n";
    std::cout << "==========================================\n";
    std::cout << std::left << std::setw(12) << "Resource ID"
              << std::setw(20) << "Name"
              << std::setW(15) << "Reservatiosn" << "\n";
    std::cout << "------------------------------------------\n";

    for (size_t i = 0; i < resources.size(); ++i)
    {
        std::cout << std::left << std::setw(12) << resources[i].getId()
                  << std:: setw(20) << resources[i].getName()
                  << std:: setw(15) << resources[i].getReservationCount() << "\n";
    }
    std::cout << "------------------------------------------\n";
}

void ReservationManager::generateMostRequestedResourcesReport()
{
    sortResourcesByPopularity(); // sorts resources using Quick Sort

    std::cout << "\n=========================================\n";
    std::cout << "       Most Requested Resources Report     \n";
    std::cout << "===========================================\n";
    std::cout << std::left << std::setw(8) << "Rank"
              << std::setw (12) << "Resource ID"
              << std::setw (20) << "Name"
              << std::setw (12) << "Total Uses" << "\n";
    std::cout << "-------------------------------------------\n";

    for (size_t i = 0; i < resources.size(); ++i)
    {
        std::cout << std::left << std::setw(8) << (i + 1)
                  << std::setw(12) << resources[i].getId()
                  << std::setw(20) << resources[i].getName()
                  << std::setw(12) << resources[i].getReservationCount() << "\n";
    }
    std::cout << "-------------------------------------------\n";
}

void ReservationManager::generateWaitingListStatsReport() const
{
    std::cout << "\n========================================\n";
    std::cout << "        Waiting List Statistics           \n";
    std::cout << "==========================================\n";
    std::cout << std::left << std::setw(15) << "Resource ID"
              << std::setw(20) << "Students Waiting" << "\n":
    std::cout << "------------------------------------------\n";

    for (size_t i = 0; i < resource.size(); ++i)
    {
        int waitingCount = WaitingList.getWaitingCountForResource(resources[i].getId());
        std::cout << std::left << std::setw(15) << resources[i].getId()
                  << std::setw(20) << waitingCount << "\n";
    }
    std::cout << "-----------------------------------------\n";
}

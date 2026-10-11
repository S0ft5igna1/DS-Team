#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H


#include "Resource.hpp"
#include "WaitingList.hpp"
#include "Reservation.hpp"
#include "CancellationHistory.hpp"
#include <string>
#include <vector>

class ReservationManager
{
    private:
    std::vector<Resource> resource;
    std::vector<Reservation> reservations;
    WaitingList waitinglist;
    CancellationHistory cancellationHistory;

    // Implementation of Quick Sort Helper Method 

    void quickSortResourceByName(std::vector<Resource>& resList, int low, int high);
    int partitionByName(std::vector<Resource>& resList, int low, int high);

    void quickSortResourcesById(std::vector<Resource>& resList, int low, int high);
    int partitionById(std::vector<Resource>& resList, int low, int high);

    void quickSortResourcesByPopularity(std::vector<Resource>& resList, int low, int high);
    int partitionByPopularity(std::vector<Resource>& resList, int low, int high);

    public:
        ReservationManager();

        // Core functions
        void addResource(const Resource& resource);
        void addReservation(const Reservation& reservation);

        // File loading
        void loadResourcesFromFile(const std::string& filename);
        void loadReservationsFromFile(const std::string& filename);

        // Searching Operations
        void sortResourcesByName();
        void sortResourcesById();
        void sortResourcesByPopularity();

        // Reporting Abilities
        void generateActiveReservationsReport() const;
        void generateResourceUtilizationReport() const;
        void generateMostRequestedResourcesReport();
        void generateWaitingListStatsReport() const;

        // Accessors
        const std::vector<Resource>& getResources() const {return resources;}
        const std::vector<Reservation>& getReservations() const { return reservations;}
};

#endif //  insert RESERVATIONMANAGER_HPP


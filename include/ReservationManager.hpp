#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H
 
#include "Reservation.hpp"
#include "CancellationHistory.hpp"
#include <string>

// This class manages reservations, allowing for creation, cancellation, and searching of reservations
class ReservationManager
{
private: // Node structure for the linked list of reservations
    struct Node
    {
        Reservation reservation; 
        Node* next;

        Node(const Reservation& reservation)
        {
            this->reservation = reservation;
            next = nullptr;
        }
    };
    //linked list for the entire system
    Node* head;
    Node* tail;
    int reservationCount;

    //checks if the recource has already been reserved on the same date
    bool reservationConflict(const std::string& resourceID, const std::string& reservationDate) const;



public:
    ReservationManager();

    ~ReservationManager();

    bool createReservation(const Reservation& reservation);

    bool cancelReservation(
        const std::string& reservationID,
        CancellationHistory& history
    );

    bool undoCancellation(CancellationHistory& history);

    void displayReservations() const;

    bool searchReservation(
        const std::string& reservationID,
        Reservation& reservation
    ) const;

    bool reservationExists(
        const std::string& reservationID
    ) const;

    int getReservationCount() const;
};

#endif
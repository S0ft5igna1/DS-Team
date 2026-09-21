#ifndef WAITING_LIST_H
#define WAITING_LIST_H

#include "Reservation.hpp"
#include <string>

class WaitingList
{
private:
    struct WaitNode
    {
        Reservation reservation;
        WaitNode* next;

        WaitNode(const Reservation& reservation)
        {
            this->reservation = reservation;
            next = nullptr;
        }
    };

    WaitNode* front;
    WaitNode* rear;

public:
    WaitingList();
    ~WaitingList();

    // Add student to back of queue
    void enqueue(const Reservation& reservation);

    // Remove first student waiting for
    // a specific resource on a specific date
    bool dequeue(
        const std::string& resourceID,
        const std::string& reservationDate,
        Reservation& reservation
    );

    // Display all students currently waiting
    void displayWaitingList() const;

    bool isEmpty() const;

    // Checks if a reservation ID exists in the waiting list
    bool reservationExists(const std::string& reservationID) const;
};

#endif
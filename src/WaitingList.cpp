#include "../include/WaitingList.hpp"
#include <iostream>

// Constructor
WaitingList::WaitingList()
{
    front = nullptr;
    rear = nullptr;
}

// Destructor
WaitingList::~WaitingList()
{
    while (front != nullptr)
    {
        WaitNode* temp = front;

        front = front->next;

        delete temp;
    }

    rear = nullptr;
}

// Add reservation request to end of queue
void WaitingList::enqueue(
    const Reservation& reservation
)
{
    WaitNode* newNode =
        new WaitNode(reservation);

    // Queue is empty
    if (rear == nullptr)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    std::cout
        << "Student added to waiting list.\n";
}

// Remove first matching student from queue
bool WaitingList::dequeue(
    const std::string& resourceID,
    const std::string& reservationDate,
    Reservation& reservation
)
{
    if (front == nullptr)
    {
        return false;
    }

    WaitNode* current = front;
    WaitNode* previous = nullptr;

    while (current != nullptr)
    {
        if (
            current->reservation.getResourceID()
                == resourceID
            &&
            current->reservation.getReservationDate()
                == reservationDate
        )
        {
            reservation =
                current->reservation;

            // Removing front
            if (current == front)
            {
                front = front->next;
            }
            else
            {
                previous->next =
                    current->next;
            }

            // Removing rear
            if (current == rear)
            {
                rear = previous;
            }

            // Queue became empty
            if (front == nullptr)
            {
                rear = nullptr;
            }

            delete current;

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

// Display waiting list
void WaitingList::displayWaitingList() const
{
    if (front == nullptr)
    {
        std::cout
            << "\nWaiting list is empty.\n";

        return;
    }

    std::cout
        << "\n===== Waiting List =====\n";

    WaitNode* current = front;

    while (current != nullptr)
    {
        current->reservation.display();

        std::cout
            << "-----------------------------\n";

        current = current->next;
    }
}

// Check if queue is empty
bool WaitingList::isEmpty() const
{
    return front == nullptr;
}


// Check if a reservation ID exists in the waiting list
bool WaitingList::reservationExists(const std::string &reservationID) const
{
    WaitNode* current = front;
    while (current != nullptr)
    {
        if (current->reservation.getReservationID() == reservationID)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

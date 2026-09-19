
#include "../include/ReservationManager.hpp" 
#include <iostream>

ReservationManager::ReservationManager()
{
    head = nullptr;
    tail = nullptr;
    reservationCount = 0;
}

ReservationManager::~ReservationManager()
{
    Node* current = head;

    while (current != nullptr)
    {
        Node* temp = current;

        current = current->next;

        delete temp;
    }
}

bool ReservationManager::reservationExists(
    const std::string& reservationID
) const
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->reservation.getReservationID()
            == reservationID)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

bool ReservationManager::createReservation(
    const Reservation& reservation
)
{
    // Basic input validation
    if (reservation.getReservationID().empty() ||
        reservation.getStudentID().empty() ||
        reservation.getStudentName().empty() ||
        reservation.getResourceID().empty() ||
        reservation.getReservationDate().empty())
    {
        std::cout << "Error: Reservation information cannot be empty.\n";
        return false;
    }

    // Prevent duplicate reservation IDs
    if (reservationExists(
        reservation.getReservationID()))
    {
        std::cout << "Error: Reservation ID already exists.\n";
        return false;
    }

    Node* newNode = new Node(reservation);

    // First reservation
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }

    // Add to end of linked list
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    reservationCount++;

    std::cout << "Reservation created successfully.\n";

    return true;
}

bool ReservationManager::cancelReservation(
    const std::string& reservationID,
    CancellationHistory& history
)
{
    if (head == nullptr)
    {
        std::cout << "There are no active reservations.\n";
        return false;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr)
    {
        if (current->reservation.getReservationID()
            == reservationID)
        {
            // Save cancelled reservation in stack
            history.push(current->reservation);

            // Removing the head
            if (current == head)
            {
                head = head->next;

                if (head == nullptr)
                {
                    tail = nullptr;
                }
            }

            // Removing another node
            else
            {
                previous->next = current->next;

                if (current == tail)
                {
                    tail = previous;
                }
            }

            delete current;

            reservationCount--;

            std::cout << "Reservation cancelled successfully.\n";
            std::cout << "Added to cancellation history.\n";

            return true;
        }

        previous = current;
        current = current->next;
    }

    std::cout << "Reservation not found.\n";

    return false;
}

bool ReservationManager::undoCancellation(
    CancellationHistory& history
)
{
    Reservation restoredReservation;

    if (!history.pop(restoredReservation))
    {
        std::cout << "There are no cancellations to undo.\n";
        return false;
    }

    Node* newNode = new Node(restoredReservation);

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    reservationCount++;

    std::cout << "Reservation restored successfully.\n";

    return true;
}

void ReservationManager::displayReservations() const
{
    if (head == nullptr)
    {
        std::cout << "\nThere are no active reservations.\n";
        return;
    }

    std::cout << "\n===== Active Reservations =====\n";

    Node* current = head;

    while (current != nullptr)
    {
        current->reservation.display();

        std::cout << "-----------------------------\n";

        current = current->next;
    }
}

bool ReservationManager::searchReservation(
    const std::string& reservationID,
    Reservation& reservation
) const
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->reservation.getReservationID()
            == reservationID)
        {
            reservation = current->reservation;

            return true;
        }

        current = current->next;
    }

    return false;
}

int ReservationManager::getReservationCount() const
{
    return reservationCount;
}
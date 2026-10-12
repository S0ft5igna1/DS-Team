
#include "../include/ReservationManager.hpp" 
#include <iostream>
#include "../include/WaitingList.hpp"
#include "../include/DateValidation.hpp"

//Constructor
ReservationManager::ReservationManager()
{
    head = nullptr;
    tail = nullptr;
    reservationCount = 0;
}

//Destructor
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

//checks if the recource has already been reserved on the same date
bool ReservationManager::reservationConflict(
    const std::string& resourceID,
    const std::string& reservationDate
) const
{
    Node* current = head; 

    while (current != nullptr) // Traverse the linked list of reservations
    {// Check if the current reservation has the same resource ID and reservation date
        if (current->reservation.getResourceID() == resourceID && 
            current->reservation.getReservationDate() == reservationDate)
        {
            return true; // Conflict found
        }

        current = current->next; 
    }

    return false; // No conflict then can create the reservation
}

//checks if the reservation ID exists 
bool ReservationManager::reservationExists(const std::string& reservationID) const
{
    Node* current = head;

    while (current != nullptr) 
    {
        if (current->reservation.getReservationID() == reservationID) // Check if the current reservation has the same reservation ID
        {
            return true; // Reservation ID exists
        }

        current = current->next;
    }

    return false; // Reservation ID does not exist
}

// Creates a new reservation
bool ReservationManager::createReservation(
    const Reservation& reservation
)
{
    // Check for empty reservation information
    if (reservation.getReservationID().empty() ||
        reservation.getStudentID().empty() ||
        reservation.getStudentName().empty() ||
        reservation.getResourceID().empty() ||
        reservation.getReservationDate().empty())
    {
        std::cout << "Error: Reservation information cannot be empty.\n";
        return false;
    }

    if (!isValidDate(reservation.getReservationDate()))
    {
        std::cout << "Error: Invalid date. Use MM/DD/YYYY.\n";
        return false;
    }

    // Prevent duplicate reservation IDs
    if (reservationExists(reservation.getReservationID()))
    {
        std::cout << "Error: Reservation ID already exists.\n";
        return false;
    }
    //check if the same resource has already been reserved on the same date
    if (reservationConflict(reservation.getResourceID(), reservation.getReservationDate()))
    {
        std::cout << "Error: Resource already reserved on this date.\n";
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


// Cancel a reservation
bool ReservationManager::cancelReservation(
    const std::string& reservationID,
    CancellationHistory& history
)
{
    if (head == nullptr) // Check if there are no active reservations
    {
        std::cout << "There are no active reservations.\n";
        return false;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr)
    { 
        // Check if the current reservation matches the provided reservation ID
        if (current->reservation.getReservationID()
            == reservationID)
        {
            // Save cancelled reservation in stack
            history.push(current->reservation);

            // Remove the head
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
                previous->next = current->next; // Update the previous node's next pointer to skip the current node

                if (current == tail) // If the current node is the tail, update the tail pointer
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

// Undo the last cancellation
bool ReservationManager::undoCancellation(CancellationHistory& history, const WaitingList& waitingList)
{
    Reservation restoredReservation;

    if (!history.peek(restoredReservation))
    {
        std::cout << "There are no cancellations to undo.\n";
        return false;
    }
    
    // Check for reservation ID is being used 
    if (reservationExists(restoredReservation.getReservationID()) ||
        waitingList.reservationExists(restoredReservation.getReservationID()))
    {


        std::cout << "Error: Cannot restore reservation. Reservation ID already exists.\n";
        return false;
    }

    //check if the same resource has already been reserved on the same date
    if (reservationConflict(restoredReservation.getResourceID(), restoredReservation.getReservationDate()))
    {

        std::cout << "Error: Cannot restore reservation. Resource already reserved on this date.\n";
        return false;
    }

    // Only remove history after all validations pass
    history.pop(restoredReservation);
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


// Display all active reservations
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

// Search for a reservation by ID
bool ReservationManager::searchReservation(
    const std::string& reservationID,
    Reservation& reservation) const
{
    Node* current = head; // Start from the head of the linked list

    while (current != nullptr)
    {
        if (current->reservation.getReservationID() // Check if the current reservation matches the provided reservation ID
            == reservationID)
        {
            reservation = current->reservation; 

            return true;
        }

        current = current->next;
    }

    return false;
}

// Get the total number of active reservations
int ReservationManager::getReservationCount() const
{
    return reservationCount;
}


int ReservationManager::countForResource(const std::string& resourceID) const
{
    int count = 0;
    Node* current = head;
    while (current != nullptr)
    {
        if (current->reservation.getResourceID() == resourceID) ++count;
        current = current->next;
    }
    return count;
}

std::vector<Reservation> ReservationManager::getReservations() const
{
    std::vector<Reservation> result;
    Node* current = head;
    while (current != nullptr)
    {
        result.push_back(current->reservation);
        current = current->next;
    }
    return result;
}

// Merge Sort, Dates are MM/DD/YYYY
static std::string dateKey(const std::string& date)
{
    return date.substr(6, 4) + date.substr(0, 2) + date.substr(3, 2);
}

static void mergeReservations(std::vector<Reservation>& items, int left, int mid, int right)
{
    std::vector<Reservation> merged;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right)
    {
        if (dateKey(items[i].getReservationDate()) <= dateKey(items[j].getReservationDate()))
            merged.push_back(items[i++]);
        else
            merged.push_back(items[j++]);
    }
    while (i <= mid) merged.push_back(items[i++]);
    while (j <= right) merged.push_back(items[j++]);
    for (int k = 0; k < static_cast<int>(merged.size()); ++k)
        items[left + k] = merged[k];
}

static void mergeSortReservations(std::vector<Reservation>& items, int left, int right)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortReservations(items, left, mid);
    mergeSortReservations(items, mid + 1, right);
    mergeReservations(items, left, mid, right);
}

void ReservationManager::displaySortedReservations() const
{
    std::vector<Reservation> items = getReservations();
    if (items.empty())
    {
        std::cout << "No active reservations.\n";
        return;
    }
    mergeSortReservations(items, 0, static_cast<int>(items.size()) - 1);
    std::cout << "\n===== Reservations Sorted by Date (Merge Sort) =====\n";
    for (const Reservation& reservation : items)
    {
        reservation.display();
        std::cout << "-----------------------------\n";
    }
}

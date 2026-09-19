#include "../include/CancellationHistory.hpp"
#include <iostream>

// Constructor to initialize the stack
CancellationHistory::CancellationHistory()
{
    top = nullptr;
}

// Destructor to clean up the stack
CancellationHistory::~CancellationHistory()
{
    while (top != nullptr) // While there are nodes in the stack
    {
        StackNode* temp = top; // Store the current top node in a temp variable
        top = top->next; // Move the top pointer to the next node in the stack
        delete temp; // Delete the temporary node to free memory
    }
}

// Add a reservation to the top of the stack
void CancellationHistory::push(const Reservation& reservation)
{
    StackNode* newNode = new StackNode(reservation); // Create a new stack node with the reservation data

    newNode->next = top; // Set the new node's next pointer to the current top of the stack

    top = newNode; //move the top pointer to the new node, making it the new top of the stack
}

// Remove the top reservation from the stack and return it
bool CancellationHistory::pop(Reservation& reservation)
{
    if (isEmpty()) //check if the stack is empty
    {
        return false;
    }

    StackNode* temp = top; // Store the current top node in a temp variable

    reservation = top->reservation; // Copy the reservation data from the top node to the provided reservation reference

    top = top->next; // Move the top pointer to the next node in the stack

    delete temp; // Delete the temp node to free memory

    return true;
}

// See the top reservation without removing it
bool CancellationHistory::peek(Reservation& reservation) const
{
    if (isEmpty()) //check if the stack is empty
    {
        return false; 
    }

    reservation = top->reservation; // Copy the reservation data from the top node to the provided reservation reference

    return true;
}

//checks if the stack is empty
bool CancellationHistory::isEmpty() const
{
    return top == nullptr;
}

//displays the cancellation history
void CancellationHistory::displayHistory() const
{
    if (isEmpty()) //check if the stack is empty
    {
        std::cout << "\nCancellation history is empty.\n";
        return;
    }

    std::cout << "\n===== Cancellation History =====\n"; 

    StackNode* current = top; // Start from the top of the stack

    while (current != nullptr) //while its not null, display the reservation details
    {
        current->reservation.display();

        std::cout << "-----------------------------\n";

        current = current->next;
    }
}
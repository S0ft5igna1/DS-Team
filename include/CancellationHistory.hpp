#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

#include "Reservation.hpp" // Include the Reservation class

// This class manages the history of canceled reservations using a custom stack data structure
class CancellationHistory
{
private: 
    struct StackNode
    {
        Reservation reservation; // The reservation data stored in the stack node
        StackNode* next; // Pointer to the next node in the stack

        StackNode(const Reservation& reservation) // Constructor to initialize a stack node 
        {
            this->reservation = reservation;
            next = nullptr;
        }
    };

    StackNode* top; // Pointer to the top of the stack 

public:
    CancellationHistory(); // Constructor to initialize the stack
    ~CancellationHistory(); // Destructor to clean up the stack

    void push(const Reservation& reservation); // Add a reservation to the top of the stack

    bool pop(Reservation& reservation); //  Remove the top reservation from the stack and return it

    bool peek(Reservation& reservation) const; //see the top reservation without removing it

    bool isEmpty() const; //checks if the stack is empty

    void displayHistory() const; //display the cancellation history
};

#endif
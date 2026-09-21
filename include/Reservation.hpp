#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation // This class represents a reservation made by a student for a specific resource
{
private:
    std::string reservationID; // Unique identifier for the reservation
    std::string studentID; // ID of the student who made the reservation
    std::string studentName; // Name of the student who made the reservation
    std::string resourceID; // ID of the resource being reserved
    std::string reservationDate; // Date when the reservation was made

public:
    Reservation(); 
    
    // Constructor to initialize a reservation with provided details
    Reservation(
        const std::string& reservationID,
        const std::string& studentID,
        const std::string& studentName,
        const std::string& resourceID,
        const std::string& reservationDate
    );

    // Getters for the reservation details
    std::string getReservationID() const;
    std::string getStudentID() const;
    std::string getStudentName() const;
    std::string getResourceID() const;
    std::string getReservationDate() const;

    // Displays the reservation details
    void display() const;
};

#endif
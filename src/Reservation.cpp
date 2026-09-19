#include "../include/Reservation.hpp"
#include <iostream>

// Default constructor to initialize an empty reservation
Reservation::Reservation() 
{
    reservationID = "";
    studentID = "";
    studentName = "";
    resourceID = "";
    reservationDate = "";
}

Reservation::Reservation( // constructor with parameters
    const std::string& reservationID,
    const std::string& studentID,
    const std::string& studentName,
    const std::string& resourceID,
    const std::string& reservationDate)
{
    this->reservationID = reservationID;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->reservationDate = reservationDate;
}

// getter for reservationID
std::string Reservation::getReservationID() const
{ 
    return reservationID;
}
// getter for studentID
std::string Reservation::getStudentID() const
{
    return studentID;
}
// getter for studentName
std::string Reservation::getStudentName() const
{
    return studentName;
}
// getter for resourceID
std::string Reservation::getResourceID() const
{
    return resourceID;
}
//  getter for reservationDate
std::string Reservation::getReservationDate() const
{
    return reservationDate;
}
// display reservation details
void Reservation::display() const
{
    std::cout << "Reservation ID: " << reservationID << '\n';
    std::cout << "Student ID: " << studentID << '\n';
    std::cout << "Student Name: " << studentName << '\n';
    std::cout << "Resource ID: " << resourceID << '\n';
    std::cout << "Reservation Date: " << reservationDate << '\n';
}
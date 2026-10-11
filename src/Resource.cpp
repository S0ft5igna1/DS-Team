#include "Resource.hpp"
#include <iostream>

// Constructor
Resource::Resource(
    const std::string& resourceId,
    const std::string& resourceName,
    const std::string& resourceType,
    bool availability
)
{
    id = resourceId;
    name = resourceName;
    type = resourceType;
    isAvailable = availability;
}

// Get resource ID
std::string Resource::getId() const
{
    return id;
}

// Get resource name
std::string Resource::getName() const
{
    return name;
}

// Get resource type
std::string Resource::getType() const
{
    return type;
}

// Get resource availability
bool Resource::getAvailability() const
{
    return isAvailable;
}

// Display individual resource cleanly
void Resource::display() const
{
    std::cout << "ID: " << id 
              << " | Name: " << name 
              << " | Type: " << type 
              << " | Status: " << (isAvailable ? "Available" : "Not Available") 
              << std::endl;
}
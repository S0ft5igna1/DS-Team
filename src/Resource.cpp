#include "Resource.hpp"

#include <fstream>
#include <sstream>
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

// Load all resources from file
std::vector<Resource> loadResources(
    const std::string& filename
)
{
    std::vector<Resource> resources;

    std::ifstream file(filename);

    std::string line;

    if (!file.is_open())
    {
        std::cerr
            << "Error opening file: "
            << filename
            << std::endl;

        return resources;
    }

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string id;
        std::string name;
        std::string type;
        std::string availabilityStr;

        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, type, '|');
        std::getline(ss, availabilityStr);

        bool availability =
            (availabilityStr == "Available");

        resources.emplace_back(
            id,
            name,
            type,
            availability
        );
    }

    file.close();

    return resources;
}

// Display all resources
void displayResources(
    const std::vector<Resource>& resources
)
{
    for (const auto& resource : resources)
    {
        std::cout
            << "ID: " << resource.getId()
            << ", Name: " << resource.getName()
            << ", Type: " << resource.getType()
            << ", Available: "
            << (resource.getAvailability()
                    ? "Available"
                    : "Not Available")
            << std::endl;
    }
}

// Display only available resources
void displayAvailableResources(
    const std::vector<Resource>& resources
)
{
    for (const auto& resource : resources)
    {
        if (resource.getAvailability())
        {
            std::cout
                << "ID: " << resource.getId()
                << ", Name: " << resource.getName()
                << ", Type: " << resource.getType()
                << ", Available: Available"
                << std::endl;
        }
    }
}

// Check whether a resource ID exists
bool resourceExists(
    const std::vector<Resource>& resources,
    const std::string& resourceID
)
{
    for (const auto& resource : resources)
    {
        if (resource.getId() == resourceID)
        {
            return true;
        }
    }

    return false;
}

// Check whether a resource is available
bool resourceIsAvailable(
    const std::vector<Resource>& resources,
    const std::string& resourceID
)
{
    for (const auto& resource : resources)
    {
        if (resource.getId() == resourceID)
        {
            return resource.getAvailability();
        }
    }

    return false;
}
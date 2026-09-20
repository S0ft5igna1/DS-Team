// Resource.cpp
#include "Resource.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

Resource::Resource(const std::string& resourceId, const std::string& resourceName, const std::string& resourceType, bool availability)
    : id(resourceId), name(resourceName), type(resourceType), isAvailable(availability) {}
    

std::string Resource::getId() const {
    return id;
}

std::string Resource::getName() const {
    return name;
}

std::string Resource::getType() const {
    return type;
}

bool Resource::getAvailability() const {
    return isAvailable;
}

std::vector<Resource> loadResources(const std::string& filename) {
    std::vector<Resource> resources;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return resources;
    }


    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, name, type, availabilityStr;
        bool availability;

        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, type, '|');
        std::getline(ss, availabilityStr);

        availability = (availabilityStr == "Available");

        resources.emplace_back(id, name, type, availability);
    }

    file.close();
    return resources;
}

void displayResources(const std::vector<Resource>& resources) {
    for (const auto& resource : resources) {
        std::cout << "ID: " << resource.getId() 
        << ", Name: " << resource.getName() 
        << ", Type: " << resource.getType() 
        << ", Available: " << (resource.getAvailability() ? "Available" : "Not Available") 
        << std::endl;
    }
}

void displayAvailableResources(const std::vector<Resource>& resources) {
    for (const auto& resource : resources) {
        if (resource.getAvailability()) {
            std::cout << "ID: " << resource.getId() 
            << ", Name: " << resource.getName() 
            << ", Type: " << resource.getType() 
            << ", Available: " << (resource.getAvailability() ? "Available" : "Not Available") 
            << std::endl;
        }
    }
}
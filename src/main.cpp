#include "Resource.hpp"
#include <iostream>

int main() {
    auto resources = loadResources("Data/resources.txt");
    for (const auto& resource : resources) {
        std::cout << "ID: " << resource.getId() << ", Name: " << resource.getName() << ", Type: " << resource.getType() << ", Available: " << (resource.getAvailability() ? "Available" : "Not Available") << std::endl;
    }
    return 0;
}
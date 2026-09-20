#include "Resource.hpp"
#include <iostream>

int main() {
    auto resources = loadResources("Data/resources.txt");
    std::cout << "All Resources:" << std::endl;
    displayResources(resources);
    std::cout << "\nAvailable Resources:" << std::endl;
    displayAvailableResources(resources);
    return 0;
}
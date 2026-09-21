
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>

class Resource {
    private:
        std::string id;
        std::string name;
        std::string type;
        bool isAvailable;

    public:
        Resource(
            const std::string& resourceId, 
            const std::string& resourceName, 
            const std::string& resourceType, 
            bool availability
                );


    // Getters 
        std::string getId() const;

        std::string getName() const;

        std::string getType() const;

        bool getAvailability() const;

};

// Load resources from resources.txt
std::vector<Resource> loadResources(
    const std::string& filename
);

// Display all resources
void displayResources(
    const std::vector<Resource>& resources
);

// Display only resources marked as available
void displayAvailableResources(
    const std::vector<Resource>& resources
);

// Check if a resource ID exists
bool resourceExists(
    const std::vector<Resource>& resources,
    const std::string& resourceID
);

// Check if a resource exists and is available
bool resourceIsAvailable(
    const std::vector<Resource>& resources,
    const std::string& resourceID
);

#endif
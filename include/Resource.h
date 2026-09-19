// Resource.h
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
        Resource(const std::string& resourceId, const std::string& resourceName, const std::string& resourceType, bool availability);

        std::string getId() const;

        std::string getName() const;

        std::string getType() const;

        bool getAvailability() const;

};

std::vector<Resource> loadResources(const std::string& filename);

    #endif
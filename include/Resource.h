// Resource.h
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
    private:
        int id;
        std::string name;
        std::string type;
        bool isAvailable;

    public:
        Resource(int resourceId, const std::string& resourceName, const std::string& resourceType, bool availability);

        int getId() const;

        std::string getName() const;

        std::string getType() const;

        bool getAvailability() const;

};
    #endif
#include "Beneficiary.h"
#include <string> // Include the necessary header file for the 'string' type

// Constructor implementation
Beneficiary::Beneficiary(int id, const string &name, int locationDistance, int maxRequests)
    : id(id), name(name), locationDistance(locationDistance), maxRequests(maxRequests) {
    
}


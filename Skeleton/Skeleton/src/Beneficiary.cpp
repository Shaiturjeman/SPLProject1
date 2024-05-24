#include "Beneficiary.h"
#include <string> // Include the necessary header file for the 'string' type
#include <stdexcept>

// Constructor implementation
Beneficiary::Beneficiary(int id, const string &name, int locationDistance, int maxRequests)
    : id(id), name(name), locationDistance(locationDistance), maxRequests(maxRequests) {
        if(id<0){
            throw std::runtime_error("id must be positive");
        }
        if(locationDistance<0){
            throw std::runtime_error("locationDistance must be positive");
        }
        if(maxRequests<0){
            throw std::runtime_error("maxRequests must be positive");
        }
    
    
}

// Get the name of the Beneficiary
const std::string &Beneficiary::getName() const {
    return name;
}

// Get the ID of the Beneficiary
int Beneficiary::getId() const {
    return id;

}

// Get the distance of the Beneficiary's location
int Beneficiary::getBeneficiaryDistance() const {
    return locationDistance;
}

// Get the maximum number of requests the Beneficiary can make  
int Beneficiary::getMaxRequests() const {
    return maxRequests;
}

// Get the number of requests the Beneficiary has made so far
int Beneficiary::getNumRequests() const {
    return requestsId.size();
}

// Check if the Beneficiary can make a new request
bool Beneficiary::canMakeRequest() const {
    return requestsId.size() < static_cast<std::vector<int>::size_type>(maxRequests);
}

// Get the IDs of the requests made by the Beneficiary
const std::vector<int> &Beneficiary::getRequestsIds() const {
    return requestsId;
}

// Add a new request to the Beneficiary's list of requests
int Beneficiary::addRequest(int RequestId) {
    if (canMakeRequest()) {
        requestsId.push_back(RequestId);
        return RequestId;
    } else {
        return -1;
    }
}

//Copy Constructor
Beneficiary::Beneficiary(const Beneficiary& other)
        : id(other.id), name(other.name), locationDistance(other.locationDistance), maxRequests(other.maxRequests), requestsId(other.requestsId) {
    }


// HospitalBeneficiary Constructor implementation
HospitalBeneficiary::HospitalBeneficiary(int id, const string &name, int locationDistance, int maxRequests)
    : Beneficiary(id, name, locationDistance, maxRequests) {
}

// Clone the HospitalBeneficiary   
HospitalBeneficiary *HospitalBeneficiary::clone() const {
    return new HospitalBeneficiary(*this);
}

// ClinicBeneficiary Constructor implementation
ClinicBeneficiary::ClinicBeneficiary(int id, const string &name, int locationDistance, int maxRequests) 
    : Beneficiary(id, name, locationDistance, maxRequests){

}

// Clone the ClinicBeneficiary
ClinicBeneficiary *ClinicBeneficiary::clone() const {
    return new ClinicBeneficiary(*this);

}






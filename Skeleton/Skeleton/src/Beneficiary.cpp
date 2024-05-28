#include "Beneficiary.h"
#include "SupplyRequest.h"
#include "MedicalWarehouse.h"
#include "Volunteer.h"
#include "Action.h" 
#include <string> 
#include <stdexcept>
#include <iostream>

// Constructor implementation
Beneficiary::Beneficiary(int id, const string &name, int locationDistance, int maxRequests)
    : id(id), name(name), locationDistance(locationDistance), maxRequests(maxRequests) {
        if(id<0){
            std::cout << "Error: id must be positive" << std::endl;
            return;
        }
        if(locationDistance<0){
            std::cout << "Error: locationDistance must be positive" << std::endl;
            return;
            
        }
        if(maxRequests<0){
            std::cout << "Error: maxRequests must be positive" << std::endl;
            return;
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
    if(requestsId.empty()){
        return true;
    }
    else if(static_cast<int>(requestsId.size()) < maxRequests){
        return true;
    }
    else{
        return false;
    }
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







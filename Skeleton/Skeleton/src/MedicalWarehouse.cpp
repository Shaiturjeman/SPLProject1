#include "MedicalWarehouse.h"
#include "Volunteer.h"
#include "SupplyRequest.h"
#include "Beneficiary.h"    
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;


// Constructor implementation
MedicalWareHouse::MedicalWareHouse(const std::string &configFilePath)
    : isOpen(false), beneficiaryCounter(0), volunteerCounter(0) {
    // Load configuration from file, initialize members
    std::ifstream configFile(configFilePath);
    if (!configFile) {
        throw std::runtime_error("Unable to open config file: " + configFilePath);
    }
    // Parse the configuration file and initialize warehouse data
}

// Start the warehouse operations
void MedicalWareHouse::start() {
    isOpen = true;
    std::cout << "Medical Warehouse is now open!" << std::endl;
}

// Add a new supply request
void MedicalWareHouse::addRequest(SupplyRequest* request) {
    pendingRequests.push_back(request);
}

// Add a new action
void MedicalWareHouse::addAction(CoreAction* action) {
    actionsLog.push_back(action);
}

// Get a Beneficiary by ID
Beneficiary& MedicalWareHouse::getBeneficiary(int beneficiaryId) const {     
    if(Beneficiaries.empty()){
        throw std::runtime_error("there is no Beneficiaries");
    }
    else{
        for(Beneficiary* beneficiary : Beneficiaries){
            if(beneficiary->getId() == beneficiaryId){
                return *beneficiary;
            }
        }
        throw std::runtime_error("there is no Beneficiary with this id");
    }
}
// Get a Volunteer by ID
Volunteer& MedicalWareHouse::getVolunteer(int volunteerId) const {
    if(volunteers.empty()){
        throw std::runtime_error("there is no volunteers");
    }
    else{
        for(Volunteer* volunteer : volunteers){
            if(volunteer->getId() == volunteerId){
                return *volunteer;
            }
        }
        throw std::runtime_error("there is no volunteer with this id");
    }
}
// Get a SupplyRequest by ID
SupplyRequest& MedicalWareHouse::getRequest(int requestId) const {
    if (pendingRequests.empty() && inProcessRequests.empty() && completedRequests.empty()){
        throw std::runtime_error("there is no requests");
    }
    else{
        for(SupplyRequest* request : pendingRequests){
            if(request->getId() == requestId){
                return *request;
            }
        }
        for(SupplyRequest* request : inProcessRequests){
            if(request->getId() == requestId){
                return *request;
            }
        }
        for(SupplyRequest* request : completedRequests){
            if(request->getId() == requestId){
                return *request;
            }
        }
        throw std::runtime_error("there is no request with this id");
    }

    
}
// Get all actions
const vector<CoreAction*>& MedicalWareHouse::getActions() const {
    if(actionsLog.empty()){
        throw std::runtime_error("there is no actions");
    }
    else{
        return actionsLog;
    }

}
// Close the warehouse
void MedicalWareHouse::close() {
    isOpen = false;
}
// Open the warehouse
void MedicalWareHouse::open() {
    isOpen = true;  
}


    
    // TODO implement


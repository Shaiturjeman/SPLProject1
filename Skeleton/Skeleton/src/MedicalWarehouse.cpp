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
Beneficiary* MedicalWareHouse::getBeneficiary(int beneficiaryId) const {     
    if(Beneficiaries.empty()){
        throw std::runtime_error("there is no Beneficiaries");
    }
    else{
        for(Beneficiary* beneficiary : Beneficiaries){
            if(beneficiary->getId() == beneficiaryId){
                return beneficiary;
            }
        }
    }
}



    
    // TODO implement


#include "MedicalWarehouse.h"
#include "Volunteer.h"
#include "SupplyRequest.h"
#include "Beneficiary.h"    
#include "Action.h"
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

//Copy Constructor
MedicalWareHouse::MedicalWareHouse(const MedicalWareHouse &other) 
    : isOpen(other.isOpen), beneficiaryCounter(other.beneficiaryCounter), volunteerCounter(other.volunteerCounter){
    for(Beneficiary* beneficiary : other.Beneficiaries){
        Beneficiary* newBeneficiary = beneficiary->clone();
        Beneficiaries.push_back(newBeneficiary);
    }
    for(Volunteer* volunteer : other.volunteers){
        Volunteer* newVolunteer = volunteer->clone();
        volunteers.push_back(newVolunteer);
    }
    for(SupplyRequest* request : other.pendingRequests){
        SupplyRequest* newRequest = new SupplyRequest(*request);
        pendingRequests.push_back(newRequest);
    }
    for(SupplyRequest* request : other.inProcessRequests){
        SupplyRequest* newRequest = new SupplyRequest(*request);
        inProcessRequests.push_back(newRequest);
    }
    for(SupplyRequest* request : other.completedRequests){
        SupplyRequest* newRequest = new SupplyRequest(*request);
        completedRequests.push_back(newRequest);
    }
    for(CoreAction* action : other.actionsLog){
        CoreAction* newAction = action->clone();
        actionsLog.push_back(newAction);
    }
}

// Start the warehouse operations
void MedicalWareHouse::start() {
    isOpen = true;
    std::cout << "Medical Warehouse is now open!" << std::endl;
}

// Add a new supply request
void MedicalWareHouse::addRequest(SupplyRequest* request) {
    if(request == nullptr){
        throw std::runtime_error("request is null");
    }
    else if(request->getStatus() == RequestStatus::PENDING){
        pendingRequests.push_back(request);
    }
    else if(request->getStatus() == RequestStatus::COLLECTING
     || request->getStatus() == RequestStatus::ON_THE_WAY){
        inProcessRequests.push_back(request);
    }
    else if(request->getStatus() == RequestStatus::DONE){
        completedRequests.push_back(request);
    }

}


// Add a new action
void MedicalWareHouse::addAction(CoreAction* action) {
    actionsLog.push_back(action);
}

// Get a Beneficiary by ID
Beneficiary& MedicalWareHouse::getBeneficiary(int beneficiaryId) const {     
    if(Beneficiaries.empty()){
        throw std::runtime_error("Beneficiary does not exist.");
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
        throw std::runtime_error("Request does not exist");
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

// Get available Inventory Manager
Volunteer* MedicalWareHouse::getInventoryManager() {
    if(volunteers.empty()){
        throw std::runtime_error("there is no volunteers");
    }
    else{
        for(Volunteer* volunteer : volunteers){
            InventoryManagerVolunteer* imv = dynamic_cast<InventoryManagerVolunteer*>(volunteer);
            if((imv != nullptr ) && (imv->isBusy() == false)){
                return volunteer;
            }
        }
        return nullptr;
    }
}

// Get the next pending request
SupplyRequest* MedicalWareHouse::getPendingRequest() {
    if(pendingRequests.empty()){
        return nullptr;
    }
    else{
        SupplyRequest* lastRequest = pendingRequests.front();
        pendingRequests.erase(pendingRequests.begin()) ;
        return lastRequest;
    }
}

// Get Courier Volunteer
Volunteer* MedicalWareHouse::getCourierVolunteer() {
    if(volunteers.empty()){
        throw std::runtime_error("there is no volunteers");
    }
    else{
        for(Volunteer* volunteer : volunteers){
            CourierVolunteer* cv = dynamic_cast<CourierVolunteer*>(volunteer);
            if((cv != nullptr ) && (cv->isBusy() == false)){
                return volunteer;
            }
        }
        return nullptr;
    }
}

// Get the next collecting request
SupplyRequest* MedicalWareHouse::getCollectingRequest() {
    if(inProcessRequests.empty()){
        return nullptr;
    }
    else{
        for(SupplyRequest* request : inProcessRequests){
            if(request->getStatus() == RequestStatus::COLLECTING){
                SupplyRequest* lastRequest = request;
                lastRequest->setStatus(RequestStatus::ON_THE_WAY);
                return lastRequest;
            }
        }

    }
    return nullptr;
}

//Incrememnt the step
void MedicalWareHouse::stepInc(){
    if(!(volunteers.empty())){
        for(Volunteer* volunteer : volunteers){
            if(CourierVolunteer* cv = dynamic_cast<CourierVolunteer*>(volunteer)){
                if(cv->isBusy()){
                    cv->step();
                }
                else{
                    int cReq = cv->getCompletedRequestId();
                    SupplyRequest request = getRequest(cReq);
                    addRequest(&request);   
                }
            }
            else if(InventoryManagerVolunteer* imv = dynamic_cast<InventoryManagerVolunteer*>(volunteer)){
                if(imv->isBusy()){
                    imv->step();
                }
                else{
                    int cReq = imv->getCompletedRequestId();
                    SupplyRequest request = getRequest(cReq);
                    addRequest(&request);
            }
        }
        

    }
    }
}

//Check the beneficiary id input
bool MedicalWareHouse::BeneficiaryCheck(int beneId){
    if(Beneficiaries.empty()){
        throw std::runtime_error("there is no Beneficiaries");
    }
    else{
        for(Beneficiary* beneficiary : Beneficiaries){
            if(beneficiary->getId() == beneId){
                if(beneficiary->canMakeRequest()){
                    beneficiaryCounter++;
                    return true;
                }
                else{
                    throw std::runtime_error("Cant place this request");
                }

            }
        }
        throw std::runtime_error("there is no Beneficiary with this id");
    }
}

//Get the number of Beneficiaries
int MedicalWareHouse::getBeneficiaryCounter(){
    return beneficiaryCounter;
}

//Add a new Beneficiary
void MedicalWareHouse::addBeneficiary(Beneficiary* beneficiary){
    Beneficiaries.push_back(beneficiary);
    beneficiaryCounter++;   
}




// Close the warehouse
void MedicalWareHouse::close(){
    isOpen = false;
    for(SupplyRequest* request : pendingRequests){
        request->toString();
    }
    for(SupplyRequest* request : inProcessRequests){
        request->toString();
    }
    for(SupplyRequest* request : completedRequests){
        request->toString();
    }
}


// Open the warehouse
void MedicalWareHouse::open() {
    isOpen = true;  
}

// Destructor implementation
MedicalWareHouse::~MedicalWareHouse() {
    for (CoreAction* action : actionsLog) {
        delete action;
    }
    for (Volunteer* volunteer : volunteers) {
        delete volunteer;
    }
    for (SupplyRequest* request : pendingRequests) {
        delete request;
    }
    for (SupplyRequest* request : inProcessRequests) {
        delete request;
    }
    for (SupplyRequest* request : completedRequests) {
        delete request;
    }
    for (Beneficiary* beneficiary : Beneficiaries) {
        delete beneficiary;
    }
}


    
    // TODO implement


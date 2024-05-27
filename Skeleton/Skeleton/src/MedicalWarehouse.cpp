#include "MedicalWarehouse.h"
#include "Volunteer.h"
#include "SupplyRequest.h"
#include "Beneficiary.h"    
#include "Action.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <sstream> 
#include <algorithm>

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
    std::string line;
     while (std::getline(configFile, line)) {
        std::istringstream iss(line);
        std::string word;
        iss >> word;

        if (word == "beneficiary") {
            std::string name, facility_type;
            int location_distance, max_requests;
            iss >> name >> facility_type >> location_distance >> max_requests;

            // Register a new Beneficiary
            RegisterBeneficiary* newAction = new RegisterBeneficiary(name, facility_type, location_distance, max_requests);
            newAction->act(*this);
            CoreAction* newCoreAction = newAction->clone();
            actionsLog.push_back(newCoreAction);


            //Add Request to the warehouse
            newCoreAction = new AddRequset(beneficiaryCounter);
            newCoreAction->act(*this);
            actionsLog.push_back(newCoreAction);
            std::cout << "Beneficiary added: " << name << " " << facility_type << " " << location_distance << " " << max_requests << std::endl;




        } 
        else if (word == "volunteer") {
            std::string name, role, managerRole;
            int param1, param2 = 0;
            iss >> name >> role >> managerRole >> param1;
            if (role + " " + managerRole == "inventory manager") {
            std::string inventory;
            iss >> inventory;
            if (role == "inventory") {
                InventoryManagerVolunteer* volunteer = new InventoryManagerVolunteer(volunteerCounter++, name, param1);
                volunteers.push_back(volunteer);
                std::cout << "Inventory Manager Volunteer added: " << volunteer->toString() << std::endl;
                }
            } 
            else if (role == "courier") {
                iss >> param2;
                CourierVolunteer* volunteer = new CourierVolunteer(volunteerCounter++, name, param1, param2);
                volunteers.push_back(volunteer);
                std::cout << "Courier Volunteer added: " << volunteer->toString() << std::endl;
            }
            std::cout << "Volunteer added: " << name << " " << role << " " << param1 << " " << param2 << std::endl;

        }
        


    }
    CoreAction* newAction = new BackupWareHouse();
    newAction->act(*this);
    actionsLog.push_back(newAction);
    std::cout << "Medical Warehouse created and BackedUp!" << std::endl;
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


// Assignment operator
MedicalWareHouse& MedicalWareHouse::operator=(const MedicalWareHouse &other){
    if(this == &other){
        return *this;
    }
    for(Volunteer* volunteer : volunteers){
        delete volunteer;
    }
    for(SupplyRequest* request : pendingRequests){
        delete request;
    }
    for(SupplyRequest* request : inProcessRequests){
        delete request;
    }
    for(SupplyRequest* request : completedRequests){
        delete request;
    }
    for(CoreAction* action : actionsLog){
        delete action;
    }
    isOpen = other.isOpen;
    beneficiaryCounter = other.beneficiaryCounter;
    volunteerCounter = other.volunteerCounter;


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
    return *this;
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
     std::vector<Volunteer*>::iterator it = volunteers.begin();
        while(it != volunteers.end()){
            InventoryManagerVolunteer* imv = dynamic_cast<InventoryManagerVolunteer*>(*it);
            if((imv != nullptr ) && (imv->isBusy() == false)){
                Volunteer* volunteer = *it;
                it = volunteers.erase(it); // remove the volunteer from the vector
                volunteers.push_back(volunteer); // push him back to the vector
                return volunteer;
            }
            else{
                ++it;
            }
        }
        return nullptr;
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
    std::vector<Volunteer*>::iterator it = volunteers.begin();
    while(it != volunteers.end()){
        CourierVolunteer* cv = dynamic_cast<CourierVolunteer*>(*it);
        if((cv != nullptr ) && (cv->isBusy() == false)){
            Volunteer* volunteer = *it;
            it = volunteers.erase(it); // remove the volunteer from the vector
            volunteers.push_back(volunteer); // push him back to the vector
            return volunteer;
        }
        else{
            ++it;
        }
    }
    return nullptr;

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

//Check the completed requests
void MedicalWareHouse::completedRequestsCheck(){
    if(inProcessRequests.empty()){
        return;
    }
    else{
        for(Volunteer* vol :volunteers){
            InventoryManagerVolunteer* invManager = dynamic_cast<InventoryManagerVolunteer*>(vol);
            CourierVolunteer* courier = dynamic_cast<CourierVolunteer*>(vol);

            if(invManager != nullptr){
                if(invManager->isBusy() == false && invManager->getCompletedRequestId() != NO_REQUEST){
                    for(SupplyRequest* request : inProcessRequests){
                        if(request->getStatus() == RequestStatus::COLLECTING){
                            CourierVolunteer* courierFree = dynamic_cast<CourierVolunteer*>(getCourierVolunteer());
                            if(courierFree != nullptr){
                                request->setCourierId(courierFree->getId());
                        }
                    }
                }
            }
            }
            else if(courier != nullptr){
                if(courier->isBusy() == false && courier->getCompletedRequestId() != NO_REQUEST){
                    for(SupplyRequest* request : inProcessRequests){
                        if(request->getStatus() == RequestStatus::ON_THE_WAY){
                            request->setStatus(RequestStatus::DONE);
                            completedRequests.push_back(request);
                            auto it = std::find(inProcessRequests.begin(), inProcessRequests.end(), request);
                            if (it != inProcessRequests.end()) {
                                inProcessRequests.erase(it);
                            }
                        }
                    }
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
                    return true;
                }
                else{
                    throw std::runtime_error("Cannnot place this request");
                }

            }
        }
    }
    return false;
}

//Get the number of Beneficiaries
int MedicalWareHouse::getBeneficiaryCounter(){
    return beneficiaryCounter;
}

//Get the number of Volunteers
int MedicalWareHouse::getVolunteerCounter(){
    return volunteerCounter;
}

//Add a new Beneficiary
void MedicalWareHouse::addBeneficiary(Beneficiary* beneficiary){
    Beneficiaries.push_back(beneficiary);
    beneficiaryCounter++;   
}


//add a new Volunteer
void MedicalWareHouse::addVolunteer(Volunteer* volunteer){
    volunteers.push_back(volunteer);
    volunteerCounter++;
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

// Check if the warehouse is open
bool MedicalWareHouse::isOpened() const {
    return isOpen;
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

    delete this;
}


    
    // TODO implement


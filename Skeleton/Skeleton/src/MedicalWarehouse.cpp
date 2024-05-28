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
        std::cout << "Erro: Unable to open config file: " << configFilePath << std::endl;
        return;
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
        } 
        else if (word == "volunteer") {
            std::string name, role1, role2;
            int param1, param2 = 0;
            iss >> name >> role1 >> role2 >> param1;
            std::string role = role1 + " " + role2;
            if (role == "inventory manager") {
                InventoryManagerVolunteer* volunteer = new InventoryManagerVolunteer(volunteerCounter, name, param1);
                volunteers.push_back(volunteer);
                std::cout << "Inventory Manager Volunteer added: " << volunteer->toString() << std::endl;
                volunteerCounter++;
            } 
            else if (role == "courier") {
                iss >> param2;
                CourierVolunteer* volunteer = new CourierVolunteer(volunteerCounter, name, param1, param2);
                addVolunteer(volunteer);
                volunteers.push_back(volunteer);
                std::cout << "Courier Volunteer added: " << volunteer->toString() << std::endl;
                volunteerCounter++;
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
    while(isOpen){
        cout << "Enter a command: ";
                string command;
                getline(cin, command);
                istringstream iss(command);
                string cmd;
                iss >> cmd;

                if (cmd == "beneficiary") {
                std::string name, facility_type;
                int location_distance, max_requests;
                iss >> name >> facility_type >> location_distance >> max_requests;

                // Register a new Beneficiary
                RegisterBeneficiary* newAction = new RegisterBeneficiary(name, facility_type, location_distance, max_requests);
                newAction->act(*backup);
                CoreAction* newCoreAction = newAction->clone();
                backup->addAction(newCoreAction);

            } 
            else if (cmd == "volunteer") {
                std::string name, role;
                int param1, param2 = 0;
                iss >> name >> role >> param1;
                if (role == "inventory") {
                    std::string managerRole;
                    iss >> managerRole;
                    if (managerRole == "manager") {
                        InventoryManagerVolunteer* volunteer = new InventoryManagerVolunteer(getVolunteerCounter() , name, param1);
                        backup->addVolunteer(volunteer);
                        std::cout << "Inventory Manager Volunteer added: " << volunteer->toString() << std::endl;
                    }
                } 
                else if (role == "courier") {
                    iss >> param2;
                    CourierVolunteer* volunteer = new CourierVolunteer(getVolunteerCounter(), name, param1, param2);
                    backup->addVolunteer(volunteer);
                    std::cout << "Courier Volunteer added: " << volunteer->toString() << std::endl;
                }
            }

            if (cmd == "request") {
                int beneficiaryId;
                iss >> beneficiaryId;
                if (iss.fail() || beneficiaryId < 0 ||beneficiaryId > beneficiaryCounter || getBeneficiary(beneficiaryId).canMakeRequest() == false){
                    cout << "Error:Cannnot place this request" << endl;
                        
                }
                else {
                    CoreAction* action = new AddRequset(beneficiaryId);
                    addAction(action);
                    action->act(*this);
                    
                    cout << "Request added successfully" << endl;
                }

            } 
                else if (cmd == "requestStatus") {
                    int requestId;
                    iss >> requestId;
                    if (iss.fail() || requestId < 0 ) {
                        cout << "Error: Invalid request ID" << endl;

                    }
                    else {
                        CoreAction* action = new PrintRequestStatus(requestId);
                        cout << "1Request status printed" << endl;
                        action->act(*this);
                        cout << "2Request status printed" << endl;
                        addAction(action);
                        cout << "3Request status printed" << endl;
                        }

                    }  
                else if (cmd == "volunteerStatus") {
                    int volunteerId;
                    iss >> volunteerId;
                    if (iss.fail() || volunteerId < 0) {    
                        cout << "Error: Invalid volunteer ID" << endl;
                    }
                    else {
                        CoreAction* action = new PrintVolunteerStatus(volunteerId);
                        action->act(*this);
                        addAction(action);
                    } 
                } 
                else if (cmd == "beneficiaryStatus") {
                    int beneficiaryId;
                    iss >> beneficiaryId;
                    if (iss.fail() || beneficiaryId < 0) {
                    cout << "Error: Invalid beneficiary ID" << endl;
                    }
                    else {
                        CoreAction* action = new PrintBeneficiaryStatus(beneficiaryId);
                        action->act(*this);
                        addAction(action);
                    }
                }
                else if(cmd == "step") {
                    int numOfSteps;
                    iss >> numOfSteps;
                    if (iss.fail()) {
                        cout << "Error: Invalid number of steps" << endl;
                    }
                    else {
                        CoreAction* action = new SimulateStep(numOfSteps);
                        action->act(*this);
                        addAction(action);
                    } 
                }
                else if (cmd == "log") {
                    if (backup->getActions().empty()) {
                        cout << "No actions have been performed yet" << endl;
                    }
                    else {
                        CoreAction* action = new PrintActionsLog();
                        action->act(*this);
                        addAction(action);
                    }    
                }
                else if (cmd == "close") {
                    if (!isOpen) {
                        cout << "Medical services are already closed." << endl;
                    }

                    else{
                        CoreAction* action = new Close();
                        action->act(*this);
                        addAction(action);
                        cout << "Medical services are now closed." << endl; 
                    } 
                        
                } 
                else {
                    cout << "Unknown command: " << cmd << endl;
                }
                
        }
}

// Add a new supply request
void MedicalWareHouse::addRequest(SupplyRequest* request) {
    if(request == nullptr){
        std::cout << "Request is null" << std::endl;
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
        std::cout << "There are no Beneficiaries(Beneficiaries Empty)" << std::endl;;
        throw std::invalid_argument("There are no Beneficiaries(Beneficiaries Empty)");

    }
    else{
        for(Beneficiary* beneficiary : Beneficiaries){
            if(beneficiary->getId() == beneficiaryId){
                return *beneficiary;
            }
        }
        std::cout << "There is no Beneficiary with this id" << std::endl;
    }
    throw std::invalid_argument("There are no Beneficiaries(Beneficiaries Empty)");
}


// Get a Volunteer by ID
Volunteer& MedicalWareHouse::getVolunteer(int volunteerId) const {
    if(volunteers.empty()){
        std::cout << "There are no Volunteers(Volunteers Empty)" << std::endl;
        throw std::invalid_argument("There are no Volunteers(Volunteers Empty)");

    }
    else{
        for(Volunteer* volunteer : volunteers){
            if(volunteer->getId() == volunteerId){
                return *volunteer;
            }
        }
        std::cout << "There is no Volunteer with this id" << std::endl;
    }
    throw std::invalid_argument("There are no Volunteers(Volunteers Empty)");
}


// Get a SupplyRequest by ID
SupplyRequest& MedicalWareHouse::getRequest(int requestId) const {
    if (pendingRequests.empty() && inProcessRequests.empty() && completedRequests.empty()){
        std::cout << "There are no Requests(Requests Empty)" << std::endl;
        throw std::invalid_argument("There are no Requests(Requests Empty)");
        
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
        std::cout << "There is no request with this id" << std::endl;
    }
    throw std::invalid_argument("There are no Requests(Requests Empty)");

    
}


// Get all actions
const vector<CoreAction*>& MedicalWareHouse::getActions() const {
    if(actionsLog.empty()){
        std::cout << "There are no actions(Actions Empty)" << std::endl;
        return actionsLog;
    }
    else{
        return actionsLog;
    }

}

// Get available Inventory Manager
Volunteer* MedicalWareHouse::getInventoryManager() {
    if(volunteers.empty()){
        std::cout << "There are no Volunteers(Volunteers Empty)" << std::endl;
        return nullptr;
    }
    std::vector<Volunteer*>::iterator it = volunteers.begin();
    while(it != volunteers.end()){
        InventoryManagerVolunteer* imv = dynamic_cast<InventoryManagerVolunteer*>(*it);
        if((imv != nullptr ) && (imv->isBusy() == false)){
            Volunteer* volunteer = *it;
            it = volunteers.erase(it); // remove the volunteer from the vector
            volunteers.push_back(volunteer); // push him back to the vector
            std::cout << "Inventory Manager Volunteer found" << std::endl;
            return volunteer;
        }
        else{
            ++it;
        }
    }
    std::cout << "All Inventory Managers are busy" << std::endl;
    return nullptr;
}


// Get the next pending request
SupplyRequest* MedicalWareHouse::getPendingRequest() {
    if(pendingRequests.empty()){
        std::cout << "There are no Requests(Requests Empty-NULLLLLLLL)" << std::endl;
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
        std::cout << "There are no Volunteers(Volunteers Empty)" << std::endl;
        return nullptr;
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
    std::cout << "All Courier Volunteers are busy" << std::endl;
    return nullptr;
}

void MedicalWareHouse::Step(){
    for(Volunteer* vol : volunteers){
        InventoryManagerVolunteer* invManager = dynamic_cast<InventoryManagerVolunteer*>(vol);
        CourierVolunteer* courier = dynamic_cast<CourierVolunteer*>(vol);
        if(invManager != nullptr){
            invManager->step();
        }
        else if(courier != nullptr){
            courier->step();
        }
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
                return lastRequest;
            }
        }

    }
    return nullptr;
}

//Check the completed requests
void MedicalWareHouse::completedRequestsCheck(){
    if(inProcessRequests.empty()){
        std::cout << "There are no requests in process" << std::endl;
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
                                courierFree->acceptRequest(*request);
                        }
                    }
                }
            }
            }
            else if(courier != nullptr){
                if(courier->isBusy() == false && courier->getCompletedRequestId() != NO_REQUEST){
                    for(SupplyRequest* request : inProcessRequests){
                        if(request->getStatus() == RequestStatus::ON_THE_WAY && courier->getDistanceLeft() == 0){
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
        std::cout << "There are no Beneficiaries(Beneficiaries Empty)" << std::endl;
    }
    else{
        for(Beneficiary* beneficiary : Beneficiaries){
            if(beneficiary->getId() == beneId){
                if(beneficiary->canMakeRequest()){
                    return true;
                }
                else{
                    std::cout << "Error: Cannnot place this request";
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


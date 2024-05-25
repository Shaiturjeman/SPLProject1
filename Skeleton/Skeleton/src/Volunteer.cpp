#include "Volunteer.h"
#include "MedicalWarehouse.h"
#include "SupplyRequest.h"
#include "Beneficiary.h"    
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

// Constructor implementation
Volunteer::Volunteer(int id, const string &name):id(id) , name(name) {
    if(id<0){
        throw std::runtime_error("id must be positive");
    }
    activeRequestId = NO_REQUEST;
    completedRequestId = NO_REQUEST;
}

//get the ID of the Volunteer
int Volunteer::getId() const{
    return id;
}  

//get the name of the Volunteer
const string& Volunteer::getName() const {
    return name;
}

//get the active request ID of the Volunteer
int Volunteer::getActiveRequestId() const {
    return activeRequestId;
}

//get the completed request ID of the Volunteer
int Volunteer::getCompletedRequestId() const {
    return completedRequestId;
}

//check if the Volunteer is busy
bool Volunteer::isBusy() const {
    int busy = getActiveRequestId();
    return busy!=NO_REQUEST;
}


//InventoryManagerVolunteer constructor
InventoryManagerVolunteer::InventoryManagerVolunteer(int id, const string &name , int coolDown):
     Volunteer(id , name) , coolDown(coolDown) {
        timeLeft = coolDown;
     }


//Clone the InventoryManagerVolunteer
InventoryManagerVolunteer * InventoryManagerVolunteer::clone() const { 
    return new InventoryManagerVolunteer(*this);
}

//Check if the InventoryManagerVolunteer can take the request
void InventoryManagerVolunteer::step() {
    if (!isBusy())
    {
        completedRequestId = activeRequestId;
        activeRequestId = NO_REQUEST;
    }
}

//Get the coolDown of the InventoryManagerVolunteer
int InventoryManagerVolunteer::getCoolDown() const {
    return coolDown;
}

// Get the time left of the InventoryManagerVolunteer
int InventoryManagerVolunteer::getTimeLeft() const {
    return timeLeft;
}


//Decrease the time left of the InventoryManagerVolunteer
bool InventoryManagerVolunteer::decreaseCoolDown() {
    if(timeLeft>0){
        timeLeft--;
    }
    return timeLeft==0;
}


//Check if the InventoryManagerVolunteer has requests left
bool InventoryManagerVolunteer::hasRequestsLeft() const {
    return activeRequestId!=NO_REQUEST;

}
    

//Check if the InventoryManagerVolunteer can take the request
bool InventoryManagerVolunteer::canTakeRequest(const SupplyRequest &request) const {
    return !isBusy();   
}

// Inventory Manager accepts the request
void InventoryManagerVolunteer::acceptRequest(const SupplyRequest &request) {
    if (isBusy())
    {
        throw std::runtime_error("Volunteer is busy");
    }
    activeRequestId = request.getId();
    timeLeft = coolDown;
}

//Convert the InventoryManagerVolunteer to string
string InventoryManagerVolunteer::toString() const{
    return "Inventory Manager Volunteer " 
    + getName() + "with ID " 
    + std::to_string(getId()) 
    + "has cool down time of: "
    +std::to_string(coolDown)
    + "and time left: " 
    +std::to_string(timeLeft);
}







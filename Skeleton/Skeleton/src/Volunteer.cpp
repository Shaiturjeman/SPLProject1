#include "Volunteer.h"
#include "MedicalWarehouse.h"
#include "SupplyRequest.h"
#include "Beneficiary.h"    
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

// Constructor implementation.
Volunteer::Volunteer(int id, const string &name):id(id) , name(name) {
    if(id<0){
        throw std::runtime_error("ID must be positive");
    }
    activeRequestId = NO_REQUEST;
    completedRequestId = NO_REQUEST;
}

//get the ID of the Volunteer.
int Volunteer::getId() const{
    return id;
}  

//get the name of the Volunteer.
const string& Volunteer::getName() const {
    return name;
}

//get the active request ID of the Volunteer.
int Volunteer::getActiveRequestId() const {
    return activeRequestId;
}

//get the completed request ID of the Volunteer.
int Volunteer::getCompletedRequestId() const {
    return completedRequestId;
}

//check if the Volunteer is busy.
bool Volunteer::isBusy() const {
    return activeRequestId!=NO_REQUEST;
}

//Volunteer destructor.
Volunteer::~Volunteer() {
    delete this;
}


//InventoryManagerVolunteer constructor.
InventoryManagerVolunteer::InventoryManagerVolunteer(int id, const string &name , int coolDown):
     Volunteer(id , name) , coolDown(coolDown) {
        timeLeft = NO_REQUEST;
     }

//Clone the InventoryManagerVolunteer.
InventoryManagerVolunteer * InventoryManagerVolunteer::clone() const { 
    return new InventoryManagerVolunteer(*this);
}

// Simulate Volunteer step.
void InventoryManagerVolunteer::step() {
    if (!isBusy())
    {
        completedRequestId = activeRequestId;
        activeRequestId = NO_REQUEST;
    }
    else{
        decreaseCoolDown();
    }
}

//Get the coolDown of the InventoryManagerVolunteer.
int InventoryManagerVolunteer::getCoolDown() const {
    return coolDown;
}

// Get the time left of the InventoryManagerVolunteer.
int InventoryManagerVolunteer::getTimeLeft() const {
    if (timeLeft==NO_REQUEST)
    {
        throw std::runtime_error("No request is being processed");
    }
    return timeLeft;
}


//Decrease the time left of the InventoryManagerVolunteer.
bool InventoryManagerVolunteer::decreaseCoolDown() {
    if(timeLeft>0){
        timeLeft--;
    }
    if (timeLeft==0)
    {
        completedRequestId = activeRequestId;
        activeRequestId = NO_REQUEST;
        timeLeft = NO_REQUEST;
        return true;
    }
    return false;
    
}


//Check if the InventoryManagerVolunteer has requests left.
bool InventoryManagerVolunteer::hasRequestsLeft() const {
    return activeRequestId != NO_REQUEST;

}

//Check if the InventoryManagerVolunteer can take the request.
bool InventoryManagerVolunteer::canTakeRequest(const SupplyRequest &request) const {
    return (!isBusy() &&  timeLeft == NO_REQUEST && request.getStatus() == RequestStatus::PENDING);
}

// Inventory Manager accepts the request.
void InventoryManagerVolunteer::acceptRequest(const SupplyRequest &request) {
    if (!canTakeRequest(request))
    {
        throw std::runtime_error("Volunteer can't take this request at this moment!");
    }
    activeRequestId = request.getId();
    timeLeft = coolDown;
}

//Convert the InventoryManagerVolunteer into a string.
string InventoryManagerVolunteer::toString() const{
    return "Volunteer ID: " + std::to_string(getId()) + "\n"
            + "IsBusy " + std::to_string(isBusy()) + "\n" ;
            if(!isBusy()) std::cout << "RequestID: None"  "\n";
            else{
                std::cout << "RequestID: " + std::to_string(getActiveRequestId()) + "\n";}
            if(timeLeft!=NO_REQUEST)    
            std::cout << "TimeLeft: " + std::to_string(timeLeft) + "\n";
            else{
                std::cout << "TimeLeft: None" << "\n";}
            std::cout << "RequestLeft ID: " + std::to_string(getActiveRequestId()) << "\n";    
            }

//InventoryManagerVolunteer destructor.
InventoryManagerVolunteer::~InventoryManagerVolunteer() {
    delete this;
}

//CourierVolunteer constructor.
CourierVolunteer::CourierVolunteer(int id, const string &name, int maxDistance, int distancePerStep):
    Volunteer(id, name) , maxDistance(maxDistance) , distancePerStep(distancePerStep) {
        distanceLeft = NO_REQUEST;
}

//Clone the CourierVolunteer.
CourierVolunteer* CourierVolunteer::clone() const {
    return new CourierVolunteer(*this);
}

// Get the distance left until the volunteer finishes his current Request.
int CourierVolunteer::getDistanceLeft() const {
    if(distanceLeft==NO_REQUEST)
    {
        throw std::runtime_error("No request is being processed");
    }
    return distanceLeft;
}

// Get the maximum distance of any request the volunteer can take.
int CourierVolunteer::getMaxDistance() const {
    return maxDistance;
}

// Get the distance the volunteer does in one step.
int CourierVolunteer::getDistancePerStep() const {
    return distancePerStep;
}

//Decreasing the distanceLeft by distancePerStep, and returns true if the courier has reached his destination, and false otherwise.
bool CourierVolunteer::decreaseDistanceLeft() {
    distanceLeft -= distancePerStep;
    if (distanceLeft<=0)
    {
        completedRequestId = activeRequestId;
        activeRequestId = NO_REQUEST;
        distanceLeft = NO_REQUEST;
        return true;
    }
    return false;
}

bool CourierVolunteer::hasRequestsLeft() const {
    return activeRequestId != NO_REQUEST;
}

//Signal if the volunteer is not busy and the Request is within the maxDistance.
bool CourierVolunteer::canTakeRequest(const SupplyRequest &request) const {
    return (!isBusy() && request.getDistance() <= maxDistance);
}

//Assign distanceLeft to Request's distance.
void CourierVolunteer::acceptRequest(const SupplyRequest &request) {
    if (!canTakeRequest(request))
    {
        throw std::runtime_error ("Volunteer can't take this request at this moment!");
    }
    activeRequestId = request.getId();
    distanceLeft = request.getDistance();
}

// Decrease distanceLeft by distancePerStep.
void CourierVolunteer::step() {
    distanceLeft -= distancePerStep;
    if (distanceLeft <= 0)
    {
        completedRequestId = activeRequestId;
        activeRequestId = NO_REQUEST;
        distanceLeft = NO_REQUEST;
    }
}

//Convert the Courier Volunteer into a string.
string CourierVolunteer::toString () const { 
    return "Volunteer ID: " + std::to_string(getId()) + "\n"
            + "IsBusy " + std::to_string(isBusy()) + "\n" ;
            if(!isBusy()) std::cout << "RequestID: None"  "\n";
            else{
                std::cout << "RequestID: " + std::to_string(getActiveRequestId()) << "\n";}
            if(distanceLeft!=NO_REQUEST)    
            std::cout << "DistanceLeft: " + std::to_string(distanceLeft) + "\n";
            else{
                std::cout << "DistanceLeft: None" << "\n";}
            std::cout << "RequestLeft ID: " + std::to_string(getActiveRequestId()) << "\n";    
            }

//CourierVolunteer destructor.
CourierVolunteer::~CourierVolunteer() {
    delete this;
}








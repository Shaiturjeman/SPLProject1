#include "SupplyRequest.h"
#include "Beneficiary.h"
#include "MedicalWarehouse.h"
#include "Volunteer.h"
#include "Action.h"
#include <iostream>
#include <string>
#include <stdexcept>

// Constructor implementation
SupplyRequest::SupplyRequest(int id, int beneficiaryId, int distance) 
    : id(id), beneficiaryId(beneficiaryId), distance(distance){
        if(id<0){
            std::cout << "Error: id must be positive" << std::endl;
            return;
        }
        if(beneficiaryId<0){
            std::cout << "Error: beneficiaryId must be positive" << std::endl;
            return;
        }
        if(distance<0){
            std::cout << "Error: distance must be positive" << std::endl;
            return;
        }
        inventoryManagerId = NO_VOLUNTEER;
        CourierId = NO_VOLUNTEER;
        status  = RequestStatus::PENDING;

}

// Copy constructor
SupplyRequest::SupplyRequest(const SupplyRequest &other)   
    : id(other.id), beneficiaryId(other.beneficiaryId), 
    distance(other.distance), status(other.status),
     inventoryManagerId(other.inventoryManagerId), 
     CourierId(other.CourierId){

    }



// Get the ID of the SupplyRequest
int SupplyRequest::getId() const {
    return id;
}

//get the ID of the Beneficiary
int SupplyRequest::getBeneficiaryId() const {
    return beneficiaryId;
}

// Set the status of the SupplyRequest
void SupplyRequest::setStatus(RequestStatus status){
    this->status = status;
}

// Set the ID of the Inventory Manager assignd to the SupplyRequest
void SupplyRequest::setInventoryManagerId(int inventoryManagerId){
    this->inventoryManagerId = inventoryManagerId;
    setStatus(RequestStatus::COLLECTING);
}

void SupplyRequest::setCourierId(int CourierId){
    this->CourierId = CourierId;
    setStatus(RequestStatus::ON_THE_WAY);
}

// Get the ID of the Inventory Manager assigned to the SupplyRequest
int SupplyRequest::getInventoryManagerId() const{
    return inventoryManagerId;
}

// Get the ID of the Courier assigned to the SupplyRequest
int SupplyRequest::getCourierId() const{
    return CourierId;
}

// Get the status of the SupplyRequest
RequestStatus SupplyRequest::getStatus() const{
    return status;
}

int SupplyRequest::getDistance() const{
    return distance;
}

string SupplyRequest::statusToString(RequestStatus status) const{
    switch (status) {
        case RequestStatus::PENDING:
            return "PENDING";
        case RequestStatus::COLLECTING:
            return "COLLECTING";
        case RequestStatus::ON_THE_WAY:
            return "ON_THE_WAY";
        case RequestStatus::DONE:
            return "DONE";
        default:
            throw std::invalid_argument("Invalid status");
    }
}



// Convert the SupplyRequest to a string
const std::string SupplyRequest::toString() const{
    return "Request ID: " + std::to_string(id) + "\n"
            + "Status: " + statusToString(status) + "\n"
            + "Beneficiary ID: " + std::to_string(beneficiaryId) + "\n"
            + "Inventory Manager: " + (inventoryManagerId == NO_VOLUNTEER ? "None" : std::to_string(inventoryManagerId)) + "\n"
            + "Courier: " + (CourierId == NO_VOLUNTEER ? "None" : std::to_string(CourierId)) + "\n";

}

// Destructor
SupplyRequest::~SupplyRequest(){
    
}

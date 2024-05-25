#include "SupplyRequest.h"
#include "Beneficiary.h"
#include "MedicalWarehouse.h"
#include "Volunteer.h"
#include "Action.h"

#include <string>
#include <stdexcept>

// Constructor implementation
SupplyRequest::SupplyRequest(int id, int benficiaryId, int distance) 
    : id(id), beneficiaryId(beneficiaryId), distance(distance){
        if(id<0){
            throw std::runtime_error("id must be posistive");
        }
        if(beneficiaryId<0){
            throw std::runtime_error("benficiaryId must be positive");
        }
        if(distance<0){
            throw std::runtime_error("distance must be positive");
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
    status = status;
}

// Set the ID of the Inventory Manager assignd to the SupplyRequest
void SupplyRequest::setInventoryManagerId(int inventoryManagerId){
    inventoryManagerId = inventoryManagerId;
    setStatus(RequestStatus::COLLECTING);
}

// Set the Id of the Courier assigned to the SupplyRequest
void SupplyRequest::setCourierId(int CourierId){
    CourierId = CourierId;
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
            return "PENDING";
    }
}



// Convert the SupplyRequest to a string
const std::string SupplyRequest::toString() const{
    return "Request ID: " + std::to_string(id) + "\n"
            + "Status: " + statusToString(status) + "\n"
            + "Beneficiary ID: " + std::to_string(beneficiaryId) + "\n"
            + "Inventory Manager: " + std::to_string(inventoryManagerId) + "\n"
            + "Courier: " + std::to_string(CourierId) + "\n";
        

}

// Destructor
SupplyRequest::~SupplyRequest(){
    delete this;
}

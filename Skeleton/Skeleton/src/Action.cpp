#include "Action.h"
#include "MedicalWarehouse.h"
#include "Volunteer.h" 
#include "Beneficiary.h"
#include <iostream>
#include <stdexcept>
#include <string>


//CoreAction Constructor
CoreAction::CoreAction() :
    status(ActionStatus::ERROR) {
    errorMsg = "Error";
    }

// Get the status of the action
ActionStatus CoreAction::getStatus() const{
    return status;
}

//Change the status of the action to Completed
void CoreAction::complete(){
    status = ActionStatus::COMPLETED;

}

//error handler
void CoreAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;  
}

//Get the error message
string CoreAction::getErrorMsg() const{
    return errorMsg;
}


//SimulateStep Constructor
SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {
}

//Make the Action in the Medical Warehouse
void SimulateStep::act(MedicalWareHouse &medWareHouse){

     int i = 0;  
    while(i < numOfSteps){
        
        // Finding a Inventory Manager Volunneter and a Supply Request from the Pending Requests
        Volunteer *currVol = medWareHouse.getInventoryManager();
        SupplyRequest *request = medWareHouse.getPendingRequest();
        if(currVol == nullptr || request == nullptr){
            error("No Inventory Manager or Request");
            medWareHouse.addRequest(request);
            return;
        }

    

        // Finding a Inventory Manager Volunneter and a Supply Request from the Pending Requests
        Volunteer *currVol = medWareHouse.getInventoryManager();
        SupplyRequest *request = medWareHouse.getPendingRequest();
        if(currVol == nullptr || request == nullptr){
            error("No Inventory Manager or Request");
            medWareHouse.addRequest(request);
            return;
        }
    
        while (true) 
        {
            request->setInventoryManagerId(currVol->getId());
            request->setStatus(RequestStatus::COLLECTING);
            dynamic_cast<InventoryManagerVolunteer*>(currVol)->acceptRequest(*request);
            medWareHouse.addRequest(request);
            request = medWareHouse.getPendingRequest();
            currVol = medWareHouse.getInventoryManager();
            if(request == nullptr){
                break;
            }
            if(currVol == nullptr){
                medWareHouse.addRequest(request);
                break;
            }
        }

        currVol = medWareHouse.getCourierVolunteer();


        // Finding a Courier Volunneter and a Supply Request from the Collecting Requests
        while(currVol != nullptr){
            request = medWareHouse.getCollectingRequest();
            if(request == nullptr){
                break;
            }
            else{
                request->setCourierId(currVol->getId());
                dynamic_cast<CourierVolunteer*>(currVol)->acceptRequest(*request);
            }
            currVol = medWareHouse.getCourierVolunteer();
            }

        // Incrementing
        medWareHouse.stepInc();
        i++;
        }
}

SimulateStep *SimulateStep::clone() const {
    return new SimulateStep(*this);
}

string SimulateStep::toString() const {
    return "SimulateStep " + std::to_string(numOfSteps);
}


//AddRequest Constructor
AddRequset::AddRequset(int id) : beneficiaryId(id) {
}

//Make the Action in the Medical Warehouse
void AddRequest::act(MedicalWareHouse &medWareHouse){
    if(medWareHouse.BeneficiaryCheck(beneficiaryId)){
        Beneficiary ben = medWareHouse.getBeneficiary(beneficiaryId);
        SupplyRequest request = new SupplyRequest(medWareHouse.beneficiaryCounter(),ben.getId(), ben.getDistance());
        medWareHouse.addRequest(request);
        std::cout << "The request is initilized with a Pending status and added to the Pending request list in the warehouse" << std::endl;
    }
    return;
}

//  Clone the AddRequest
AddRequset *AddRequset::clone() const {
    return new AddRequset(*this);
}

//Convert the AddRequest to a string 
string AddRequset::toString() const {
    return "Add request " + std::to_string(beneficiaryId);
}

//RegisterBeneficiary Constructor
RegisterBeneficiary::RegisterBeneficiary(const string &beneficiaryName, const string &beneficiaryType, int distance, int maxRequests) 
    : beneficiaryName(beneficiaryName), beneficiaryType(beneficiaryType), distance(distance), maxRequests(maxRequests) {
}

//Register the Beneficiary in the Medical Warehouse
void RegisterBeneficiary::act(MedicalWareHouse &medWareHouse){
    int id = medWareHouse.getBeneficiaryCounter();
    if(beneficiaryType == "HospitalBeneficiary"){
        HospitalBeneficiary *ben = new HospitalBeneficiary(id, beneficiaryName, distance, maxRequests);
        medWareHouse.addBeneficiary(ben);
        std::cout << "The Hospital Beneficiary is added to the Beneficiary list in the warehouse" << std::endl;
    }
    else if(beneficiaryType == "ClinicBeneficiary"){
        ClinicBeneficiary *ben = new ClinicBeneficiary(id, beneficiaryName, distance, maxRequests);
        medWareHouse.addBeneficiary(ben);
        std::cout << "The Clinic Beneficiary is added to the Beneficiary list in the warehouse" << std::endl;
    }
    else{
        error("Invalid Beneficiary Type");
    }

}

//Clone the RegisterBeneficiary
RegisterBeneficiary *RegisterBeneficiary::clone() const {
    return new RegisterBeneficiary(*this);
}

//Convert the RegisterBeneficiary to a string
string RegisterBeneficiary::toString() const {
    return "Register Beneficiary " + beneficiaryName + " " "+ Hospital/Clinic "+ " " + std::to_string(distance) + " " + std::to_string(maxRequests);
}


//PrintRequestStatus Constructor
PrintRequestStatus::PrintRequestStatus(int id) : requestId(id) {
}

//Print the Request Status in the Medical Warehouse
void PrintRequestStatus::act(MedicalWareHouse &medWareHouse){
    SupplyRequest request = medWareHouse.getRequest(requestId);
    std::cout << request.toString() << std::endl;
}

//Clone the PrintRequestStatus
PrintRequestStatus *PrintRequestStatus::clone() const {
    return new PrintRequestStatus(*this);
}

//Convert the PrintRequestStatus to a string
string PrintRequestStatus::toString() const {
    return "Print Request Status " + std::to_string(requestId);
}

//PrintBeneficiaryStatus Constructor
PrintBeneficiaryStatus::PrintBeneficiaryStatus(int BeneficiaryId) : beneficiaryId(BeneficiaryId) {
}

//Print the Beneficiary Status in the Medical Warehouse
void PrintBeneficiaryStatus::act(MedicalWareHouse &medWareHouse){
    Beneficiary ben = medWareHouse.getBeneficiary(beneficiaryId);
    std::cout << ben.toString() << std::endl;
}
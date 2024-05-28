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


//Copy Constructor
CoreAction::CoreAction(const CoreAction &other) {
    status = other.status;
    errorMsg = other.errorMsg;
}

//Assignment Operator
CoreAction &CoreAction::operator=(const CoreAction &other) {
    if (this != &other) {
        status = other.status;
        errorMsg = other.errorMsg;
    }
    return *this;
}

//Destructor
CoreAction::~CoreAction() {
    
}



//SimulateStep Constructor
SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {
}

//Make the Action in the Medical Warehouse
void SimulateStep::act(MedicalWareHouse &medWareHouse){


    for (int i = 0; i < numOfSteps; ++i) {
        std::cout << "Step " << i << std::endl;
        // Stage 1: Supply request processing
        InventoryManagerVolunteer *invManager = dynamic_cast<InventoryManagerVolunteer*>(medWareHouse.getInventoryManager());
        SupplyRequest *pendingRequest = medWareHouse.getPendingRequest();


        while (invManager != nullptr && pendingRequest != nullptr){
            
            std::cout << "first loop "  << std::endl;
            invManager->acceptRequest(*pendingRequest);
            std::cout << "The inventory manager get the request" << std::endl;
            pendingRequest->setInventoryManagerId(invManager->getId());
            std::cout << "The request is being processed by the Inventory Manager" << std::endl;
            medWareHouse.addRequest(pendingRequest);
            invManager = dynamic_cast<InventoryManagerVolunteer*>(medWareHouse.getInventoryManager());
            if(invManager != nullptr){
                pendingRequest = medWareHouse.getPendingRequest();

            }
            
            
        }
            CourierVolunteer* courier = dynamic_cast<CourierVolunteer*>(medWareHouse.getCourierVolunteer());
            SupplyRequest* collectingRequest = medWareHouse.getCollectingRequest();

            while (courier != nullptr && collectingRequest != nullptr){
                std::cout << "second loop "  << std::endl;
                courier->acceptRequest(*collectingRequest);
                std::cout << "The courier get the collecting request" << std::endl;
                collectingRequest->setCourierId(courier->getId());
                std::cout << "The collecting request is being processed by the Courier" << std::endl;
                medWareHouse.addRequest(collectingRequest);
                courier = dynamic_cast<CourierVolunteer*>(medWareHouse.getCourierVolunteer());
                if(courier != nullptr){
                    collectingRequest = medWareHouse.getCollectingRequest();
                }
            }
        // Stage 2: Advance time units
        // Decrement the timeLeft for each Inventory Manager
        medWareHouse.Step();


        // Stage 3: Volunteer and Supply Requests Completion Check
        medWareHouse.completedRequestsCheck();
            
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
void AddRequset::act(MedicalWareHouse &medWareHouse){
        Beneficiary& ben = medWareHouse.getBeneficiary(beneficiaryId);
        int num = ben.getNumRequests();
        SupplyRequest* request = new SupplyRequest(num,ben.getId(), ben.getBeneficiaryDistance());
        ben.addRequest(num);
        medWareHouse.addRequest(request);
        std::cout << "The request is initilized with a Pending status and added to the Pending request list in the warehouse" << std::endl;
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
    : beneficiaryName(beneficiaryName),
     beneficiaryType(beneficiaryType == "hospital" ? beneficiaryType::Hospital : beneficiaryType::Clinic)
    ,distance(distance)
    , maxRequests(maxRequests) {

        
}


//Register the Beneficiary in the Medical Warehouse
void RegisterBeneficiary::act(MedicalWareHouse &medWareHouse){
    int id = medWareHouse.getBeneficiaryCounter();
    if(beneficiaryType == ::beneficiaryType::Hospital){
        HospitalBeneficiary *ben = new HospitalBeneficiary(id, beneficiaryName, distance, maxRequests);
        medWareHouse.addBeneficiary(ben);
        std::cout << "The Hospital Beneficiary is added to the Beneficiary list in the warehouse" << std::endl;
    }
    else if(beneficiaryType == ::beneficiaryType::Clinic){
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
    std::cout << " I got here1" << std::endl;
    std::cout << request.toString() << std::endl;
    std::cout << " I got here2" << std::endl;
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
    Beneficiary& ben = medWareHouse.getBeneficiary(beneficiaryId);
    std::cout << "Beneficiary ID: " + std::to_string(ben.getId()) + "\n"
            + "Request Id: "  << std::endl;
            for(int i : ben.getRequestsIds()){
                std::cout << i << " " << "\n" << std::endl;
            }
    std::cout << "Status: " << std::endl;
            for (int i : ben.getRequestsIds()){
                SupplyRequest request = medWareHouse.getRequest(i);
                std::cout << request.statusToString(request.getStatus()) << "\n" << std::endl;
            }
    std::cout << "Requst Left: " << ben.getMaxRequests() - ben.getNumRequests() << std::endl;
    }

    //Clone the PrintBeneficiaryStatus
    PrintBeneficiaryStatus *PrintBeneficiaryStatus::clone() const {
        return new PrintBeneficiaryStatus(*this);
    }

    //Convert the PrintBeneficiaryStatus to a string
    string PrintBeneficiaryStatus::toString() const {
        return "Print Beneficiary Status " + std::to_string(beneficiaryId);
    }

    //Print Volunteer Status Constructor
    PrintVolunteerStatus::PrintVolunteerStatus(int VolunteerId) : volunteerId(VolunteerId) {
    }

    //Print the Volunteer Status in the Medical Warehouse
    void PrintVolunteerStatus::act(MedicalWareHouse &medWareHouse){
        Volunteer& vol = medWareHouse.getVolunteer(volunteerId);
        std::cout << vol.toString() << std::endl;

    }


    //Clone the PrintVolunteerStatus
    PrintVolunteerStatus *PrintVolunteerStatus::clone() const {
        return new PrintVolunteerStatus(*this);
    }

    //Convert the PrintVolunteerStatus to a string
    string PrintVolunteerStatus::toString() const {
        return "Print Volunteer Status " + std::to_string(volunteerId);
    }

    //Print Actions Log Constructor
    PrintActionsLog::PrintActionsLog() {
    }

    //Print the Actions Log in the Medical Warehouse
    void PrintActionsLog::act(MedicalWareHouse &medWareHouse){
        for(CoreAction* action : medWareHouse.getActions()){
            std::cout << action->toString() << std::endl;
        }
    }

    //Clone the PrintActionsLog
    PrintActionsLog *PrintActionsLog::clone() const {
        return new PrintActionsLog(*this);
    }

    //Convert the PrintActionsLog to a string
    string PrintActionsLog::toString() const {
        return "Print Actions Log";
    }

    //Close Constructor
    Close::Close() {
    }

    //Close the Medical Warehouse
    void Close::act(MedicalWareHouse &medWareHouse){
        medWareHouse.close();
        std::cout << "Medical Warehouse is now closed!" << std::endl;
        // delete &medWareHouse;
        
        
        
    }

    //Clone the Close
    Close *Close::clone() const {
        return new Close(*this);
    }

    //Convert the Close to a string
    string Close::toString() const {
        return "Close";
    }

    //BackupWareHouse Constructor
    BackupWareHouse::BackupWareHouse() {
    }

    //Backup the Medical Warehouse
    void BackupWareHouse::act(MedicalWareHouse &medWareHouse){
        if (backup != nullptr) {
            delete backup;  // delete the old backup
        }
        backup = new MedicalWareHouse(medWareHouse);  // create a new backup
        std::cout << this->toString() << std::endl;

    }

    //Clone the BackupWareHouse
    BackupWareHouse *BackupWareHouse::clone() const {
        return new BackupWareHouse(*this);
    }

    //Convert the BackupWareHouse to a string
    string BackupWareHouse::toString() const {
        return "Updates the backup with the latest state of the warehouse.";
    }


    //RestoreWareHouse Constructor
    RestoreWareHouse::RestoreWareHouse() {
    }

    //Restore the Medical Warehouse
    void RestoreWareHouse::act(MedicalWareHouse &medWareHouse){
        if (backup == nullptr) {
            error("No backup available");
            return;
        }
        medWareHouse = *backup;
        std::cout << this->toString() << std::endl;
    }


    //Clone the RestoreWareHouse
    RestoreWareHouse *RestoreWareHouse::clone() const {
        return new RestoreWareHouse(*this);
    }

    //Convert the RestoreWareHouse to a string
    string RestoreWareHouse::toString() const {
        return "Restore the warehouse to the last backup.";
    }

   
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
    errorMsg = "ERROR";
    }

// Get the status of the action
ActionStatus CoreAction::getStatus() const{
    return status;
}
//Change the status of the action to Completed
void CoreAction::complete(){
    status = ActionStatus::COMPLETED;
    errorMsg = "COMPLETED";

}

//error handler
void CoreAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    errorMsg = "ERROR: " ;  
}

//Get the error message
string CoreAction::getErrorMsg() const{
    if (errorMsg == "ERROR")
    {
        return "ERROR";
    }
    return "COMPLETED";
    
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
            
            invManager->acceptRequest(*pendingRequest);
            pendingRequest->setInventoryManagerId(invManager->getId());
            medWareHouse.addRequest(pendingRequest);
            invManager = dynamic_cast<InventoryManagerVolunteer*>(medWareHouse.getInventoryManager());
            if(invManager != nullptr){
                pendingRequest = medWareHouse.getPendingRequest();

            }
            
            
        }
            SupplyRequest* collectingRequest = medWareHouse.getCollectingRequest();
            if(collectingRequest != nullptr){
                CourierVolunteer* courier = dynamic_cast<CourierVolunteer*>(medWareHouse.getCourierVolunteer(collectingRequest->getDistance()));;
                while (courier != nullptr && collectingRequest != nullptr){
                    courier->acceptRequest(*collectingRequest);
                    collectingRequest->setCourierId(courier->getId());
                    collectingRequest = medWareHouse.getCollectingRequest();
                    if(collectingRequest != nullptr){
                        courier = dynamic_cast<CourierVolunteer*>(medWareHouse.getCourierVolunteer(collectingRequest->getDistance()));
                    }
                    else{
                        courier = nullptr;
                    }
                }
            }
        // Stage 2: Advance time units
        // Decrement the timeLeft for each Inventory Manager
        medWareHouse.Step();


        // Stage 3: Volunteer and Supply Requests Completion Check
        medWareHouse.completedRequestsCheck();

            
    }
    complete();
}
SimulateStep *SimulateStep::clone() const {
    return new SimulateStep(*this);
}

string SimulateStep::toString() const {
    return "step " + std::to_string(numOfSteps) + " " + getErrorMsg();
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
        complete();
    return;
}

//  Clone the AddRequest
AddRequset *AddRequset::clone() const {
    return new AddRequset(*this);
}

//Convert the AddRequest to a string 
string AddRequset::toString() const {
    return "request " + std::to_string(beneficiaryId) + " " + getErrorMsg()  ;
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
        complete(); 
    }
    else if(beneficiaryType == ::beneficiaryType::Clinic){
        ClinicBeneficiary *ben = new ClinicBeneficiary(id, beneficiaryName, distance, maxRequests);
        medWareHouse.addBeneficiary(ben);
        complete();
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
    return "Register Beneficiary " + beneficiaryName + 
     " " "+ Hospital/Clinic "+ " " 
     + std::to_string(distance) + " "
     + std::to_string(maxRequests) + " "
     + getErrorMsg();
}


//PrintRequestStatus Constructor
PrintRequestStatus::PrintRequestStatus(int id) : requestId(id) {
}

//Print the Request Status in the Medical Warehouse
void PrintRequestStatus::act(MedicalWareHouse &medWareHouse){
    SupplyRequest request = medWareHouse.getRequest(requestId);
    std::cout << "Request ID: " << request.getId() << "\n"
              << "Request Status: " << request.statusToString(request.getStatus()) << "\n"
              << "Beneficiary ID: " << request.getBeneficiaryId() << "\n"
              << "Inventory Manager: " << (request.getInventoryManagerId() == NO_VOLUNTEER ? "None" : std::to_string(request.getInventoryManagerId())) << "\n"
              << "Courier: " << (request.getCourierId() == NO_VOLUNTEER ? "None" : std::to_string(request.getCourierId())) << std::endl;
              complete();
}

//Clone the PrintRequestStatus
PrintRequestStatus *PrintRequestStatus::clone() const {
    return new PrintRequestStatus(*this);
}

//Convert the PrintRequestStatus to a string
string PrintRequestStatus::toString() const {
    return "requestStatus " + std::to_string(requestId) + " " + getErrorMsg();
}

//PrintBeneficiaryStatus Constructor
PrintBeneficiaryStatus::PrintBeneficiaryStatus(int BeneficiaryId) : beneficiaryId(BeneficiaryId) {
}


//Print the Beneficiary Status in the Medical Warehouse
void PrintBeneficiaryStatus::act(MedicalWareHouse &medWareHouse){
    Beneficiary& ben = medWareHouse.getBeneficiary(beneficiaryId);
    std::cout << "Beneficiary ID: " + std::to_string(ben.getId()) << std::endl;

    for(int i : ben.getRequestsIds()){
        SupplyRequest request = medWareHouse.getRequest(i);
        std::cout << "Request ID: " << i << std::endl;
        std::cout << "Request Status: " << request.statusToString(request.getStatus()) << std::endl;
    }
    std::cout << "Requests Left: " << ben.getMaxRequests() - ben.getNumRequests() << std::endl;
    complete();
}

    //Clone the PrintBeneficiaryStatus
    PrintBeneficiaryStatus *PrintBeneficiaryStatus::clone() const {
        return new PrintBeneficiaryStatus(*this);
    }

    //Convert the PrintBeneficiaryStatus to a string
    string PrintBeneficiaryStatus::toString() const {
        return "beneficiaryStatus " + std::to_string(beneficiaryId) + " " + getErrorMsg();
    }

    //Print Volunteer Status Constructor
    PrintVolunteerStatus::PrintVolunteerStatus(int VolunteerId) : volunteerId(VolunteerId) {
    }

    //Print the Volunteer Status in the Medical Warehouse
    void PrintVolunteerStatus::act(MedicalWareHouse &medWareHouse){
        Volunteer& vol = medWareHouse.getVolunteer(volunteerId);
        std::cout << vol.toString() << std::endl;
        complete();

    }


    //Clone the PrintVolunteerStatus
    PrintVolunteerStatus *PrintVolunteerStatus::clone() const {
        return new PrintVolunteerStatus(*this);
    }

    //Convert the PrintVolunteerStatus to a string
    string PrintVolunteerStatus::toString() const {
        return "volunteerStatus " + std::to_string(volunteerId) + " " + getErrorMsg();
    }

    //Print Actions Log Constructor
    PrintActionsLog::PrintActionsLog() {
    }

    //Print the Actions Log in the Medical Warehouse
    void PrintActionsLog::act(MedicalWareHouse &medWareHouse){
        for(CoreAction* action : medWareHouse.getActions()){
            std::cout << action->toString() << std::endl;
        }
        complete();
    }

    //Clone the PrintActionsLog
    PrintActionsLog *PrintActionsLog::clone() const {
        return new PrintActionsLog(*this);
    }

    //Convert the PrintActionsLog to a string
    string PrintActionsLog::toString() const {
        string res ;
        res+= "log";
        res+= " ";
        res+= getErrorMsg();
        return res;
    }

    //Close Constructor
    Close::Close() {
    }

    //Close the Medical Warehouse
    void Close::act(MedicalWareHouse &medWareHouse){
        medWareHouse.close();
        complete();
        return;
        
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
        complete();

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
        complete();
    }


    //Clone the RestoreWareHouse
    RestoreWareHouse *RestoreWareHouse::clone() const {
        return new RestoreWareHouse(*this);
    }

    //Convert the RestoreWareHouse to a string
    string RestoreWareHouse::toString() const {
        return "Restore the warehouse to the last backup.";
    }

   
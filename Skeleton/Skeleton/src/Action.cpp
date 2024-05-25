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
void CoreAcrion::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;  
}

//Get the error message
string CoreAction::getErrorMsg() const{
    return errorMsg;
}


//SimulateStep Constructor
SimulateStep::SimulateStep(int numOfSteps) : numOfsteps(numOfSteps) {
}

//Make the Action in the Medical Warehouse
void SimulateStep::act(MedicalWrehouse &medWareHouse){
    //Supply request Processing
    for(int i =0; i< medWareHouse.volunteers.size(); i++){
        if(!(medicalWarHouse.volunteers[i].isBusy())){
            
        }

        
        
        
    }

}
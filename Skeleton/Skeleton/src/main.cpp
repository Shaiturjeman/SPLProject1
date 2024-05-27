#include "MedicalWarehouse.h"
#include "Action.h"
#include "Beneficiary.h"
#include "Volunteer.h"
#include "SupplyRequest.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

MedicalWareHouse* backup = nullptr;

int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "usage: warehouse <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    MedicalWareHouse  medWareHouse(configurationFile);
    medWareHouse.start();
    if(backup!=nullptr){
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
                    InventoryManagerVolunteer* volunteer = new InventoryManagerVolunteer(backup->getVolunteerCounter() , name, param1);
                    backup->addVolunteer(volunteer);
                    std::cout << "Inventory Manager Volunteer added: " << volunteer->toString() << std::endl;
                }
            } 
            else if (role == "courier") {
                iss >> param2;
                CourierVolunteer* volunteer = new CourierVolunteer(backup->getVolunteerCounter(), name, param1, param2);
                backup->addVolunteer(volunteer);
                std::cout << "Courier Volunteer added: " << volunteer->toString() << std::endl;
            }
        }

        if (cmd == "request") {
            int beneficiaryId;
            iss >> beneficiaryId;
            if (iss.fail() || beneficiaryId < 0 || !backup->BeneficiaryCheck(beneficiaryId)) {
                cout << "Error:Cannnot place this request" << endl;
                    
            }
            else {
                CoreAction* action = new AddRequset(beneficiaryId);
                action->act(medWareHouse);
                medWareHouse.addAction(action);
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
                    action->act(medWareHouse);
                    medWareHouse.addAction(action);
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
                    action->act(medWareHouse);
                    medWareHouse.addAction(action);
                } 
            } 
            else if (cmd == "beneficiaryStatus") {
                int beneficiaryId;
                iss >> beneficiaryId;
                if (iss.fail() || beneficiaryId < 0 || !backup->BeneficiaryCheck(beneficiaryId)) {
                cout << "Error: Invalid beneficiary ID" << endl;
                }
                else {
                    CoreAction* action = new PrintBeneficiaryStatus(beneficiaryId);
                    action->act(medWareHouse);
                    medWareHouse.addAction(action);
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
                    action->act(medWareHouse);
                    medWareHouse.addAction(action);
                } 
            }
            else if (cmd == "log") {
                if (backup->getActions().empty()) {
                    cout << "No actions have been performed yet" << endl;
                }
                else {
                    CoreAction* action = new PrintActionsLog();
                    action->act(medWareHouse);
                    medWareHouse.addAction(action);
                }    
            }
            else if (cmd == "close") {
                if (!backup->isOpened()) {
                    cout << "Medical services are already closed." << endl;
                }

                else{
                    CoreAction* action = new Close();
                    action->act(medWareHouse);
                    medWareHouse.addAction(action);
                    cout << "Medical services are now closed." << endl; 
                } 
                    
            } 
            else {
                cout << "Unknown command: " << cmd << endl;
            }
            
        
    	delete backup;
    	backup = nullptr;
        }
    return 0;
    }
///workspaces/SPLProject1/Skeleton/Skeleton/bin/my_program /workspaces/SPLProject1/Skeleton/Skeleton/configFileExample.txt
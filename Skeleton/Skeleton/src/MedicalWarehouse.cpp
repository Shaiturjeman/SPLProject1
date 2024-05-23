#include "MedicalWarehouse.h"
#include "Volunteer.h"
#include "SupplyRequest.h"
#include "Beneficiary.h"    

#include <vector>
#include <iostream>

using namespace std;
MedicalWareHouse:: MedicalWareHouse(const string &configFilePath) {
    volunteers = std::vector<Volunteer*>();      
    pendingRequests = std::vector<SupplyRequest*>();   
    inProcessRequests = std::vector<SupplyRequest*>();
    completedRequests = std::vector<SupplyRequest*>();  
    Beneficiaries = std::vector<Beneficiary*>();    
}
    void MedicalWareHouse::start(){
        std:: cout << "Medical services are now open!" << std::endl;
    }
    
      
    
    // TODO implement


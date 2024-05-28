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
        
    	delete backup;
    	backup = nullptr;
        }
    return 0;
    }
///workspaces/SPLProject1/Skeleton/Skeleton/bin/my_program /workspaces/SPLProject1/Skeleton/Skeleton/configFileExample.txt
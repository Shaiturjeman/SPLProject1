#include "MedicalWarehouse.h"
#include <iostream>

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
        std:: string input;
        std:: cin >> input;
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}
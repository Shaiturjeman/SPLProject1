#include "Volunteer.h"
#include "MedicalWarehouse.h"
#include "SupplyRequest.h"
#include "Beneficiary.h"    
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

Volunteer::Volunteer(int id, const string &name):id(id) , name(name) , activeRequestId(NO_REQUEST) , completedRequestId(NO_REQUEST) {}

int Volunteer::getId() const{
    return id;
}

const string& Volunteer::getName() const {
    return name;
}

int Volunteer::getActiveRequestId() const {
    return activeRequestId;
}

int Volunteer::getCompletedRequestId() const {
    return completedRequestId;
}

bool Volunteer::isBusy() const {
    int busy = getActiveRequestId();
    return busy!=NO_REQUEST;
}

InventoryManagerVolunteer::InventoryManagerVolunteer(int id, const string &name , int coolDown): Volunteer(id , name) , coolDown(coolDown) {}

InventoryManagerVolunteer * InventoryManagerVolunteer::clone() const { 
    return new InventoryManagerVolunteer(*this);
}

void InventoryManagerVolunteer::step() {
    if (!isBusy())
    {
        completedRequestId = activeRequestId;
        activeRequestId = NO_REQUEST;
    }
}

int InventoryManagerVolunteer::getCoolDown() const {
    return coolDown;
}

int InventoryManagerVolunteer::getTimeLeft() const {
    return timeLeft;
}

bool InventoryManagerVolunteer::decreaseCoolDown() {
    timeLeft--;
    return timeLeft==0;
}

bool InventoryManagerVolunteer::hasRequestsLeft() const {
    
}
    




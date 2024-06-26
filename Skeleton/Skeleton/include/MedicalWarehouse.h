#pragma once
#include <string>
#include <vector>

#include "SupplyRequest.h"
#include "Beneficiary.h"

class CoreAction;
class Volunteer;

// Warehouse responsible for Volunteers, Beneficiaries Actions, and SupplyRequests.


class MedicalWareHouse {

    public:
        MedicalWareHouse(const string &configFilePath);
        void start();
        void addRequest(SupplyRequest* request);
        void addAction(CoreAction* action);
        Beneficiary &getBeneficiary(int beneficiaryId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        SupplyRequest &getRequest(int requestId) const;
        const vector<CoreAction*> &getActions() const;
        void close();
        void open();
        Volunteer *getInventoryManager();
        SupplyRequest *getPendingRequest();
        Volunteer *getCourierVolunteer(int distance);
        SupplyRequest *getCollectingRequest();
        void addVolunteer(Volunteer* volunteer);
        void stepInc();
        bool BeneficiaryCheck(int beneId);
        int getBeneficiaryCounter();
        int getVolunteerCounter();
        void completedRequestsCheck();
        void addBeneficiary(Beneficiary* beneficiary);
        void Step();
        ~MedicalWareHouse();

        // Copy constructor
        MedicalWareHouse(const MedicalWareHouse &other);
        // Assignment operator
        MedicalWareHouse& operator=(const MedicalWareHouse &other);


    private:
        bool isOpen;
        vector<CoreAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<SupplyRequest*> pendingRequests;
        vector<SupplyRequest*> inProcessRequests;
        vector<SupplyRequest*> completedRequests;
        vector<Beneficiary*> Beneficiaries;
        int beneficiaryCounter; //For assigning unique Beneficiary IDs
        int volunteerCounter; //For assigning unique volunteer IDs
};
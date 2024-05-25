#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

enum class RequestStatus {
    PENDING,
    COLLECTING,
    ON_THE_WAY,
    DONE,
};

#define NO_VOLUNTEER -1

class SupplyRequest {

    public:
        SupplyRequest(int id, int beneficiaryId, int distance);
        int getId() const;
        int getBeneficiaryId() const;
        void setStatus(RequestStatus status);
        void setInventoryManagerId(int inventoryManagerId);
        void setCourierId(int CourierId);
        int getInventoryManagerId() const;
        int getCourierId() const;
        RequestStatus getStatus() const;
        const string toString() const;
        int getDistance() const;
        string statusToString(RequestStatus) const;
        

        //Copy constructor
        SupplyRequest(const SupplyRequest& other);

        //Destructor
        ~SupplyRequest();

    private:
        const int id;
        const int beneficiaryId;
        const int distance;
        RequestStatus status;
        int inventoryManagerId; //Initialized to NO_VOLUNTEER if no inventoryManager has been assigned yet
        int CourierId; //Initialized to NO_VOLUNTEER if no Courier has been assigned yet
};
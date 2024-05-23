#pragma once
#include <string>
#include <vector>
#include "SupplyRequest.h"
using std::string;
using std::vector;

#define NO_REQUEST -1

class Volunteer {
    public:
        Volunteer(int id, const string &name);
        int getId() const;
        const string &getName() const;
        int getActiveRequestId() const;
        int getCompletedRequestId() const;
        bool isBusy() const; // Signal whether the volunteer is currently processing a Request    
        virtual bool canTakeRequest(const SupplyRequest &request) const = 0; // Signal if the volunteer can take the Request.      
        virtual void acceptRequest(const SupplyRequest &request) = 0; // Prepare for new Request(Reset activeRequestId,TimeLeft,DistanceLeft)
                
        virtual void step() = 0; //Simulate volunteer step,if the volunteer finished the Request, transfer activeRequestId to completedRequestId

        virtual string toString() const = 0;
        virtual Volunteer* clone() const = 0; //Return a copy of the volunteer

    protected:
        int completedRequestId; //Initialized to NO_Request if no Request has been completed yet
        int activeRequestId; //Initialized to NO_Request if no Request is being processed
    
    private:
        const int id;
        const string name;

};


class InventoryManagerVolunteer: public Volunteer {

    public:
        InventoryManagerVolunteer(int id, const string &name, int coolDown);
        InventoryManagerVolunteer *clone() const override;
        void step() override;
        int getCoolDown() const;
        int getTimeLeft() const;
        bool decreaseCoolDown();//Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
        bool hasRequestsLeft() const;
        bool canTakeRequest(const SupplyRequest &request) const override;
        void acceptRequest(const SupplyRequest &request) override;
        string toString() const override;
    
    private:
        const int coolDown; // The time it takes the volunteer to process a Request
        int timeLeft; // Time left until the volunteer finishes his current Request
};


class CourierVolunteer: public Volunteer {

    public:
        CourierVolunteer(int id, const string &name, int maxDistance, int distancePerStep);
        CourierVolunteer *clone() const override;

        int getDistanceLeft() const;
        int getMaxDistance() const;
        int getDistancePerStep() const;  
        bool decreaseDistanceLeft(); //Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
        bool hasRequestsLeft() const;
        bool canTakeRequest(const SupplyRequest &request) const override; // Signal if the volunteer is not busy and the Request is within the maxDistance
        void acceptRequest(const SupplyRequest &request) override; // Assign distanceLeft to Request's distance
        void step() override; // Decrease distanceLeft by distancePerStep
        string toString() const override;

    private:
        const int maxDistance; // The maximum distance of ANY Request the volunteer can take
        const int distancePerStep; // The distance the volunteer does in one step
        int distanceLeft; // Distance left until the volunteer finishes his current Request
};
#pragma once
#include <string>
#include <vector>
#include "MedicalWarehouse.h"
using std::string;
using std::vector;

enum class ActionStatus{
    COMPLETED, ERROR
};

enum class beneficiaryType{
    Soldier, Civilian
};


class CoreAction{
    public:
        CoreAction();
        ActionStatus getStatus() const;
        virtual void act(MedicalWareHouse & medWareHouse)=0;
        virtual string toString() const=0;
        virtual CoreAction* clone() const=0;

    protected:
        void complete();
        void error(string errorMsg);
        string getErrorMsg() const;

    private:
        string errorMsg;
        ActionStatus status;
};

class SimulateStep : public CoreAction {

    public:
        SimulateStep(int numOfSteps);
        void act(MedicalWareHouse  &medWareHouse) override;
        std::string toString() const override;
        SimulateStep *clone() const override;

    private:
        const int numOfSteps;
};

class AddRequset : public CoreAction {
    public:
        AddRequset(int id);
        void act(MedicalWareHouse  &medWareHouse) override;
        string toString() const override;
        AddRequset *clone() const override;
    private:
        const int beneficiaryId;
};


class RegisterBeneficiary : public CoreAction {
    public:
        RegisterBeneficiary(const string &beneficiaryName, const string &beneficiaryType, int distance, int maxRequests);
        void act(MedicalWareHouse &medWareHouse) override;
        RegisterBeneficiary *clone() const override;
        string toString() const override;
    private:
        const string beneficiaryName;
        const ::beneficiaryType beneficiaryType;
        const int distance;
        const int maxRequests;
};



class PrintRequestStatus : public CoreAction {
    public:
        PrintRequestStatus(int id);
        void act(MedicalWareHouse &medWareHouse) override;
        PrintRequestStatus *clone() const override;
        string toString() const override;
    private:
        const int requestId;
};

class PrintBeneficiaryStatus: public CoreAction {
    public:
        PrintBeneficiaryStatus(int BeneficiaryId);
        void act(MedicalWareHouse &medWareHouse) override;
        PrintBeneficiaryStatus *clone() const override;
        string toString() const override;
    private:
        const int beneficiaryId;
};


class PrintVolunteerStatus : public CoreAction {
    public:
        PrintVolunteerStatus(int id);
        void act(MedicalWareHouse &medWareHouse) override;
        PrintVolunteerStatus *clone() const override;
        string toString() const override;
    private:
        const int volunteerId;
};


class PrintActionsLog : public CoreAction {
    public:
        PrintActionsLog();
        void act(MedicalWareHouse &medWareHouse) override;
        PrintActionsLog *clone() const override;
        string toString() const override;
    private:
};

class Close : public CoreAction {
    public:
        Close();
        void act(MedicalWareHouse &medWareHouse) override;
        Close *clone() const override;
        string toString() const override;
    private:
};

class BackupWareHouse : public CoreAction {
    public:
        BackupWareHouse();
        void act(MedicalWareHouse &medWareHouse) override;
        BackupWareHouse *clone() const override;
        string toString() const override;
    private:
};


class RestoreWareHouse : public CoreAction {
    public:
        RestoreWareHouse();
        void act(MedicalWareHouse &medWareHouse) override;
        RestoreWareHouse *clone() const override;
        string toString() const override;
    private:
};
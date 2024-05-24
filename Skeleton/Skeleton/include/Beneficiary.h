#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;



class Beneficiary {
    public:
        Beneficiary(int id, const string &name, int locationDistance, int maxRequests);
        const string &getName() const;
        int getId() const;
        int getBeneficiaryDistance() const;
        int getMaxRequests() const; //Returns maxRequests
        int getNumRequests() const; //Returns num of requests the Beneficiary has made so far
        bool canMakeRequest() const; //Returns true if the Beneficiary didn't reach max requests
        const vector<int> &getRequestsIds() const;
        int addRequest(int RequestId); //return RequestId if request was added successfully, -1 otherwise

        virtual Beneficiary *clone() const = 0; // Return a copy of the Beneficiary


        //Copy Constructor
        Beneficiary(const Beneficiary& other);
             
        


    private:
        const int id;
        const string name;
        const int locationDistance;
        const int maxRequests;
        vector<int> requestsId;


};



class HospitalBeneficiary: public Beneficiary {
    public:
        HospitalBeneficiary(int id, const string &name, int locationDistance, int maxRequests);
        HospitalBeneficiary *clone() const override;
    
    private:
        
};

class ClinicBeneficiary: public Beneficiary {
    public:
        ClinicBeneficiary(int id, const string &name, int locationDistance, int maxRequests);
        ClinicBeneficiary *clone() const override;
    
    private:
        
};
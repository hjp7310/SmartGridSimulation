#pragma once
#include "Common.h"
#include "ControlMsg.h"

class ControlCenter : public omnetpp::cSimpleModule
{
private:
    std::vector<PowerPlantInfo> powerPlants;
    std::vector<SubstationInfo> substations;
    std::vector<ConsumerInfo> consumers;
    std::vector<int> dayConsumption;
    std::vector<int> dayCost;
    int currentConsumption;
    int cnt;
protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;
private:
    void SetPowerPlant();
    void SetSubstation();
    void SetCoustomer();
    void SetDayConsumption();
    void SetDayCost();
    void ShowBill();
    std::vector<ControlMsg*> GenerateMessage();
    void ForwardMessage(omnetpp::cMessage *msg);
    void DistributePower(const int totalProduction);
    void DistributeLogic(std::vector<std::pair<PowerPlantInfo, int>> &powerPlantProduction, const int totalProduction);
};

Define_Module(ControlCenter);

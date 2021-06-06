#pragma once
#include "Common.h"
#include "ControlMsg.h"

class ControlCenter : public omnetpp::cSimpleModule
{
private:
    std::vector<PowerPlantInfo> powerPlants;
    std::vector<SubstationInfo> substations;
protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;
private:
    void SetPowerPlant();
    void SetSubstation();
    ControlMsg* GenerateMessage(PowerPlantInfo &info);
    void ForwardMessage(ControlMsg &msg);
};

Define_Module(ControlCenter);

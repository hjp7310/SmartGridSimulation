#pragma once
#include "Common.h"
#include "ControlMsg.h"
#include "Power.h"

class Consumer : public omnetpp::cSimpleModule
{
private:
    std::vector<int> dayConsumption;
    int cnt;
    int ess;
protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage* msg) override;
private:
    void SetDayConsumption();
};

Define_Module(Consumer);

#pragma once
#include "Common.h"
#include "ControlMsg.h"
#include "Power.h"

class PowerPlant : public omnetpp::cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage* msg) override;
};

Define_Module(PowerPlant);

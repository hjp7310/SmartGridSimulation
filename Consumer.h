#pragma once
#include "Common.h"
#include "ControlMsg.h"
#include "Power.h"

class Consumer : public omnetpp::cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage* msg) override;
};

Define_Module(Consumer);

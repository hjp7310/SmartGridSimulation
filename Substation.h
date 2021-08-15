#pragma once
#include "Common.h"
#include "ControlMsg.h"
#include "Power.h"

class Substation : public omnetpp::cSimpleModule
{
private:
    int watt;
    int inputSize;
    int outputSize;
    int cnt;
protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage* msg) override;
};

Define_Module(Substation);

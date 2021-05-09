#pragma once
#include "Common.h"

class PowerPlant : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage* msg) override;
};

Define_Module(PowerPlant);

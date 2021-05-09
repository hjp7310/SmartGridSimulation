#pragma once
#include "Common.h"

class Substation : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage* msg) override;
};

Define_Module(Substation);

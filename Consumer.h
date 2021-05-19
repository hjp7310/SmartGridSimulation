#pragma once
#include "Common.h"

class Consumer : public cSimpleModule
{
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage* msg) override;
};

Define_Module(Consumer);

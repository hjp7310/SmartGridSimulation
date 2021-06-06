#pragma once
#include "Common.h"

class Power : public omnetpp::cMessage
{
private:
	int watt;
public:
	Power(int watt);
	int GetWatt();
};

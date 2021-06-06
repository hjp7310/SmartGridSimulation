#pragma once
#include "Common.h"

class ControlMsg : public omnetpp::cMessage
{
protected:
	int nodeId;
	NodeAttribute nodeAttribute;
	ControlCommand controlCommand;
	int watt;
public:
	ControlMsg(int nodeId, NodeAttribute nodeAttribute, ControlCommand controlCommand, int watt);
	int GetNodeId();
	ControlCommand GetCommand();
	int GetWatt();
};

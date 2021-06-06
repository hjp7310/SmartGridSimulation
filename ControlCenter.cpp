#include "ControlCenter.h"

void ControlCenter::initialize()
{
	SetPowerPlant();
	SetSubstation();

	std::vector<ControlMsg*> msgs;

	for (auto powerPlant : powerPlants)
	{
		msgs.push_back(GenerateMessage(powerPlant));
	}

	for (auto msg : msgs)
	{
		scheduleAt(0.0, msg);
	}
}

void ControlCenter::handleMessage(omnetpp::cMessage *msg)
{
	ControlMsg *tmsg = dynamic_cast<ControlMsg*>(msg);
	if (tmsg->GetCommand() == ControlCommand::GeneratePower)
	{
		send(tmsg, "control_gate$o", tmsg->GetNodeId() - 1);
	}
}

void ControlCenter::SetPowerPlant()
{
	this->powerPlants.push_back(PowerPlantInfo{ 1, 100, 1000 });
	this->powerPlants.push_back(PowerPlantInfo{ 2, 100, 1000 });
}

void ControlCenter::SetSubstation()
{
	this->substations.push_back(SubstationInfo{ 1 });
	this->substations.push_back(SubstationInfo{ 2 });
}

ControlMsg* ControlCenter::GenerateMessage(PowerPlantInfo &info)
{
	return new ControlMsg(info.nodeId, NodeAttribute::PowerPlant, ControlCommand::GeneratePower, 500);
}

void ControlCenter::ForwardMessage(ControlMsg &msg)
{
}
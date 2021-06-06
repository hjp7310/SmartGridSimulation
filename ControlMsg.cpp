#include "ControlMsg.h"

ControlMsg::ControlMsg(int nodeId, NodeAttribute nodeAttribute, ControlCommand controlCommand, int watt)
{
	this->nodeId = nodeId;
	this->nodeAttribute = nodeAttribute;
	this->controlCommand = controlCommand;
	this->watt = watt;
}

int ControlMsg::GetNodeId()
{
	return this->nodeId;
}

ControlCommand ControlMsg::GetCommand()
{
	return this->controlCommand;
}

int ControlMsg::GetWatt()
{
	return this->watt;
}

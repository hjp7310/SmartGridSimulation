#include "Consumer.h"

void Consumer::initialize()
{

}

void Consumer::handleMessage(omnetpp::cMessage* msg)
{
	ControlMsg* cmsg = new ControlMsg(0, NodeAttribute::Consumer, ControlCommand::ConsumptionInfo, 0);
	send(cmsg, "control_gate$o", 0);
}

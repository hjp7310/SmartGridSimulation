#include "PowerPlant.h"

void PowerPlant::initialize()
{

}

void PowerPlant::handleMessage(omnetpp::cMessage* msg)
{
	ControlMsg *tmsg = dynamic_cast<ControlMsg*>(msg);
	ControlMsg* cmsg = new ControlMsg(0, NodeAttribute::PowerPlant, ControlCommand::TransmissionInfo, tmsg->GetWatt());
	send(cmsg, "control_gate$o", 0);
	Power *nmsg = new Power(tmsg->GetWatt());
	send(nmsg, "power_gate_out", 0);
}

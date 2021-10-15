#include "Substation.h"

void Substation::initialize()
{
	this->watt = 0;
	this->inputSize = par("power_gate_in");
	this->outputSize = par("power_gate_out");
	this->cnt = 0;
}

void Substation::handleMessage(omnetpp::cMessage* msg)
{
	if (this->cnt < this->inputSize)
	{
		Power *tmsg = dynamic_cast<Power*>(msg);
		this->watt += tmsg->GetWatt();
		this->cnt++;
	}
	if (this->cnt == this->inputSize)
	{
		ControlMsg* cmsg = new ControlMsg(0, NodeAttribute::Substation, ControlCommand::TransmissionInfo, this->watt);
		send(cmsg, "control_gate$o", 0);
		for (int i = 0; i < this->outputSize; i++)
		{
			Power *nmsg = new Power(this->watt);
			send(nmsg, "power_gate$o", i + this->inputSize);
		}
		EV << "Substation " << " Power: " << this->watt << "\n";
		this->watt = 0;
		this->cnt = 0;
	}
}

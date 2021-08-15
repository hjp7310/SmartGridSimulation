#include "Consumer.h"

void Consumer::initialize()
{
	cnt = 0;

	SetDayConsumption();
}

void Consumer::handleMessage(omnetpp::cMessage* msg)
{
	ControlMsg* cmsg = new ControlMsg(0, NodeAttribute::Consumer, ControlCommand::ConsumptionInfo, dayConsumption[cnt]);
	send(cmsg, "control_gate$o", 0);
	EV << "Consumer " << " Time: " << cnt + 1 << " Power: " << cmsg->GetWatt() << "\n";
	cnt++;
}

void Consumer::SetDayConsumption()
{
	std::ifstream fin("consumer_data.txt");
	char data[64];
	while (!fin.eof())
	{
		fin >> data;
		dayConsumption.push_back(atoi(data));
	}
	fin.close();

	if (dayConsumption.size() != HOUR)
	{
		EV << "ERROR: Hour\n";
	}
	
	for (auto &dc : dayConsumption)
	{
		std::mt19937 gen(getId());
		std::uniform_int_distribution<int> dis(-dc / 20, dc / 20);
		dc = dc + dis(gen);
	}
}

#include "ControlCenter.h"

void ControlCenter::initialize()
{
	this->currentConsumption = 0;
	this->cnt = 0;

	SetPowerPlant();
	SetSubstation();
	SetCoustomer();
	SetDayConsumption();
	SetDayCost();

	std::vector<ControlMsg*> msgs = GenerateMessage();

	for (auto msg : msgs)
	{
		scheduleAt(0.0, msg);
	}
}

void ControlCenter::handleMessage(omnetpp::cMessage *msg)
{
	ControlMsg *tmsg = dynamic_cast<ControlMsg*>(msg);

	switch (tmsg->GetCommand())
	{
	case ControlCommand::GeneratePower:
		send(tmsg, "control_gate$o", tmsg->GetNodeId() - 1);
		char buf[64];
		EV << "ControlCenter " << " Time: " << cnt + 1
			<< " Node ID: " << itoa(tmsg->GetNodeId(), buf, 10) << " Power: " << tmsg->GetWatt() << "\n";
		break;
	case ControlCommand::TransmissionInfo:
		break;
	case ControlCommand::ConsumptionInfo:
		if (consumers[0].Consumption.size() < HOUR)
		{
			consumers[(cnt % consumers.size())].Consumption.push_back(tmsg->GetWatt());

			if ((this->cnt + 1) % this->consumers.size() == 0)
			{
				int totalConsumption = dayConsumption[(cnt + 1) / consumers.size()];
				DistributePower(totalConsumption);
			}
		}
		if ((cnt + 1) / consumers.size() == HOUR)
		{
			ShowBill();
		}
		this->cnt++;
		break;
	default:
		break;
	}
}

void ControlCenter::SetPowerPlant()
{
	this->powerPlants.push_back(PowerPlantInfo{ 1, 100, 10000, 10 });
	this->powerPlants.push_back(PowerPlantInfo{ 2, 100, 1000, 5 });
}

void ControlCenter::SetSubstation()
{
	this->substations.push_back(SubstationInfo{ 1 });
	this->substations.push_back(SubstationInfo{ 2 });
}

void ControlCenter::SetCoustomer()
{
	this->consumers.push_back(ConsumerInfo{ 1 });
	this->consumers.push_back(ConsumerInfo{ 2 });
	this->consumers.push_back(ConsumerInfo{ 3 });
}

void ControlCenter::SetDayConsumption()
{
	std::ifstream fin("consumer_data.txt");
	char data[64];
	while (!fin.eof())
	{
		fin >> data;
		int totalData = (atoi(data) + atoi(data) / 10) * consumers.size();
		dayConsumption.push_back(totalData);
	}
	fin.close();

	if (dayConsumption.size() != HOUR)
	{
		EV << "ERROR: Hour\n";
	}
}

void ControlCenter::SetDayCost()
{
	std::ifstream fin("bill_data.txt");
	char data[64];
	while (!fin.eof())
	{
		fin >> data;
		dayCost.push_back(atoi(data));
	}
	fin.close();

	if (dayCost.size() != HOUR)
	{
		EV << "ERROR: Hour\n";
	}
}

void ControlCenter::ShowBill()
{
	for (auto consumer : consumers)
	{
		int totalCost = 0;
		for (int i = 0; i < HOUR; i++)
		{
			totalCost += consumer.Consumption[i] * dayCost[i];
		}
		char buf[64];
		EV << "Total Bill "
			<< " Node ID: " << itoa(consumer.nodeId, buf, 10) << " Cost: " << totalCost << "\n";
	}
}

std::vector<ControlMsg*> ControlCenter::GenerateMessage()
{
	std::vector<ControlMsg*> msg;
	std::vector<std::pair<PowerPlantInfo, int>>* costOderPPs = new std::vector<std::pair<PowerPlantInfo, int>>();
	DistributeLogic(*costOderPPs, dayConsumption[0]);

	for (const auto &costOderPP : *costOderPPs)
	{
		msg.push_back(new ControlMsg(costOderPP.first.nodeId, NodeAttribute::PowerPlant, ControlCommand::GeneratePower, costOderPP.second));
	}

	return msg;
}

void ControlCenter::ForwardMessage(omnetpp::cMessage *msg)
{
	ControlMsg* tmsg = dynamic_cast<ControlMsg*>(msg);
	send(tmsg, "control_gate$o", tmsg->GetNodeId() - 1);
	char buf[64];
	EV << "ControlCenter " << " Time: " << (cnt + 1) / consumers.size() + 1
		<< " Node ID: " << itoa(tmsg->GetNodeId(), buf, 10) << " Power: " << tmsg->GetWatt() << "\n";
}

void ControlCenter::DistributePower(const int totalProduction)
{
	std::vector<std::pair<PowerPlantInfo, int>> *costOderPPs = new std::vector<std::pair<PowerPlantInfo, int>>();
	DistributeLogic(*costOderPPs, totalProduction);

	for (const auto &costOderPP : *costOderPPs)
	{
		ControlMsg* cmsg = new ControlMsg(costOderPP.first.nodeId, NodeAttribute::PowerPlant, ControlCommand::GeneratePower, costOderPP.second);
		ForwardMessage(cmsg);
	}

	delete costOderPPs;
}

void ControlCenter::DistributeLogic(std::vector<std::pair<PowerPlantInfo, int>> &powerPlantProduction, const int totalProduction)
{
	int minProduction = 0;
	int maxProduction = 0;

	for (const auto &powerPlant : powerPlants)
	{
		powerPlantProduction.push_back(std::make_pair(powerPlant, 0));
		minProduction += powerPlant.minPowerGen;
		maxProduction += powerPlant.maxPowerGen;
	}
	std::sort(powerPlantProduction.begin(), powerPlantProduction.end(),
		[](std::pair<PowerPlantInfo, int> lpp, std::pair<PowerPlantInfo, int> rpp) { return lpp.first.cost < rpp.first.cost; });

	if (minProduction >= totalProduction)
	{
		for (auto &costOderPP : powerPlantProduction)
		{
			costOderPP.second = costOderPP.first.minPowerGen;
		}
	}
	else if (maxProduction < totalProduction)
	{
		EV << "ERROR: Lack of Power\n";
	}
	else
	{
		int lackProduction = totalProduction - minProduction;

		for (auto &costOderPP : powerPlantProduction)
		{
			int ppMax = costOderPP.first.maxPowerGen - costOderPP.first.minPowerGen;
			if (0 < (ppMax - lackProduction))
			{
				costOderPP.second = costOderPP.first.minPowerGen + lackProduction;
				lackProduction = 0;
			}
			else
			{
				costOderPP.second = costOderPP.first.maxPowerGen;
				lackProduction = lackProduction - ppMax;
			}
		}
	}

	std::sort(powerPlantProduction.begin(), powerPlantProduction.end(),
		[](std::pair<PowerPlantInfo, int> lpp, std::pair<PowerPlantInfo, int> rpp) { return lpp.first.nodeId < rpp.first.nodeId; });
}

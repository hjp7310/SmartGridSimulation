#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <omnetpp.h>

enum class NodeAttribute
{
	ControlCenter,
	PowerPlant,
	Substation,
	Consumer
};

enum class ControlCommand
{
	GeneratePower,
	TransmissionInfo,
	ConsumptionInfo
};

struct PowerPlantInfo
{
	int nodeId;
	int minPowerGen;
	int maxPowerGen;
};

struct SubstationInfo
{
	int nodeId;
};
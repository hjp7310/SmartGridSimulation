#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <utility>
#include <algorithm>
#include <vector>
#include <random>
#include <sstream>
#include <iterator>
#include <omnetpp.h>

#define HOUR 24

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
	int cost;
};

struct SubstationInfo
{
	int nodeId;
};

struct ConsumerInfo
{
	int nodeId;
	std::vector<int> Consumption;
};
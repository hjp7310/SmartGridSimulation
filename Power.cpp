#include "Power.h"

Power::Power(int watt)
{
	this->watt = watt;
}

int Power::GetWatt()
{
	return this->watt;
}

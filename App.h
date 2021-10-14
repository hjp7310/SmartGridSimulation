#pragma once
#include "Common.h"
#include "ControlMsg.h"

#include "inet/applications/tcpapp/TcpGenericServerApp.h"
#include "inet/applications/tcpapp/TcpBasicClientApp.h"

//namespace inet
//{
//	//class ControlCenterApp : public TcpGenericServerApp
//	//{
//	//protected:
//	//	virtual void sendBack(cMessage* msg);
//	//};
//	//
//	//Define_Module(ControlCenterApp);
//
//	//
//
//	class PowerPlantApp : public omnetpp::cModule
//	{
//
//	};
//
//	Define_Module(PowerPlantApp);
//
//	//
//
//	class SubstationtApp : public omnetpp::cModule
//	{
//
//	};
//
//	Define_Module(SubstationtApp);
//
//	//
//
//	class ConsumerApp : public TcpBasicClientApp
//	{
//	protected:
//	//	virtual void socketDataArrived(TcpSocket* socket, Packet* msg, bool urgent) override;
//		virtual void sendRequest();
//	};
//
//	Define_Module(ConsumerApp);
//}

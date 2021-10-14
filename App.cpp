#include "App.h"

#include "inet/applications/common/SocketTag_m.h"
#include "inet/applications/tcpapp/GenericAppMsg_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Message.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/tcp/TcpCommand_m.h"

#include "inet/applications/tcpapp/GenericAppMsg_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TimeTag_m.h"

//namespace inet
//{
//    //void ControlCenterApp::sendBack(inet::cMessage* msg)
//    //{
//    //    cPacket* packet = dynamic_cast<cPacket*>(msg);
//    //
//    //    if (packet) {
//    //        msgsSent++;
//    //        bytesSent += packet->getByteLength();
//    //        emit(packetSentSignal, packet);
//    //
//    //        EV_INFO << "sending \"" << packet->getName() << "\" to TCP, "
//    //            << packet->getByteLength() << " bytes\n";
//    //    }
//    //    else {
//    //        EV_INFO << "sending \"" << msg->getName() << "\" to TCP\n";
//    //    }
//    //
//    //    auto& tags = getTags(msg);
//    //    tags.addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::tcp);
//    //
//    //    send(msg, "socketOut");
//    //}
//
//    //void ConsumerApp::socketDataArrived(TcpSocket* socket, Packet* msg, bool urgent)
//    //{
//    //    TcpAppBase::socketDataArrived(socket, msg, urgent);
//    //
//    //    if (numRequestsToSend > 0) {
//    //        EV_INFO << "reply arrived\n";
//    //
//    //        if (timeoutMsg) {
//    //            simtime_t d = simTime() + par("thinkTime");
//    //            rescheduleOrDeleteTimer(d, MSGKIND_SEND);
//    //        }
//    //    }
//    //    else if (socket->getState() != TcpSocket::LOCALLY_CLOSED) {
//    //        EV_INFO << "reply to last request arrived, closing session\n";
//    //        close();
//    //    }
//    //}
//
//
//    void ConsumerApp::sendRequest()
//    {
//        long requestLength = par("requestLength");
//        long replyLength = par("replyLength");
//        if (requestLength < 1)
//            requestLength = 1;
//        if (replyLength < 1)
//            replyLength = 1;
//    
//        const auto& payload = makeShared<GenericAppMsg>();
//        Packet* packet = new Packet("data");
//        payload->setChunkLength(B(requestLength));
//        payload->setExpectedReplyLength(B(replyLength));
//        payload->setServerClose(false);
//        payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
//        packet->insertAtBack(payload);
//    
//        EV_INFO << "sending request with " << requestLength << " bytes, expected reply length " << replyLength << " bytes,"
//            << "remaining " << numRequestsToSend - 1 << " request\n";
//    
//        sendPacket(packet);
//    }
//}

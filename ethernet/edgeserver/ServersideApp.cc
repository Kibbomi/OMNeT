/*
 * Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the
 * implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>

#include "ServersideApp.h"

#include "inet/common/TimeTag_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/NodeStatus.h"

namespace inet {

Define_Module(ServersideApp);

void ServersideApp::initialize(int stage)
{
    EV<<" Server Call initialize."<<std::endl;
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        localSap = par("localSAP");

        // statistics
        packetsSent = packetsReceived = 0;

        // socket
        llcSocket.setOutputGate(gate("out"));
        llcSocket.setCallback(this);

        f = (int)ceil(uniform(1,5));
        capacity = 10;

        WATCH(packetsSent);
        WATCH(packetsReceived);
    }
}

void ServersideApp::handleStartOperation(LifecycleOperation *operation)
{
    EV<<" Server Call handleStartOperation."<<std::endl;
    EV_INFO << "Starting application\n";
    registerDsap(localSap);
}

void ServersideApp::handleStopOperation(LifecycleOperation *operation)
{
    EV<<" Server Call handleStopOperation."<<std::endl;
    EV_INFO << "Stop the application\n";
    llcSocket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void ServersideApp::handleCrashOperation(LifecycleOperation *operation)
{
    EV<<" Server Call handleCrashOperation."<<std::endl;
    EV_INFO << "Crash the application\n";
    if (operation->getRootModule() != getContainingNode(this))
        llcSocket.destroy();
}

void ServersideApp::socketClosed(Ieee8022LlcSocket *socket)
{
    EV<<" Server Call socketClosed."<<std::endl;
    if (operationalState == State::STOPPING_OPERATION && !llcSocket.isOpen())
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void ServersideApp::handleMessageWhenUp(cMessage *msg)
{
    EV<<" Server Call handleMessageWhenUp."<<std::endl;
    llcSocket.processMessage(msg);
}

void ServersideApp::socketDataArrived(Ieee8022LlcSocket*, Packet *msg)
{
    EV<<" Server Call socketDataArrived."<<std::endl;
    EV_INFO << "Received packet `" << msg->getName() << "'\n";


    if(strcmp(msg->getName(),"ERSReq") == 0)
    {
        const auto& req = msg->peekAtFront<ERSReq>();
        if (req == nullptr)
            throw cRuntimeError("data type error: not an ERSReq arrived in packet %s", msg->str().c_str());

        emit(packetReceivedSignal, msg);


        //discard the packet because 'this' is a Edge server.
        if(req->getFindTarget()==OnlyRSU)
        {
            delete msg;
            return;
        }

        MacAddress srcAddr = msg->getTag<MacAddressInd>()->getSrcAddress();
        int srcSap = msg->getTag<Ieee802SapInd>()->getSsap();

        //save RSU data
        Format_RSUCluster item = Format_RSUCluster();
        item.addr = srcAddr;

        std::string key_string = item.addr.str();

        if(RSUs.count(key_string) == 0){
            RSUs.insert(std::make_pair(key_string,item));

            EV<< "ES : RSU Table\n";
            for(auto iter = RSUs.begin(); iter!=RSUs.end(); ++iter)
                EV<<"MAC : "<<(*iter).first<<'\n';
        }
        else
        {
            EV<< "ES already has this RSU, discard request.\n";
            delete msg;
            return ;
        }


        //send back packets asked by RSU.
        Packet *outPacket = new Packet("ERSResp", IEEE802CTRL_DATA);
        const auto& outPayload = makeShared<ERSResp>();

        //Edge server information
        outPayload->setChunkLength(B(21));
        outPayload->setCapacity(capacity);
        outPayload->setF(f);
        outPayload->setInfo(OnlyES);

        //not used
        outPayload->setY(0);
        outPayload->setX(0);
        outPayload->setCoverage(0);
        outPacket->insertAtBack(outPayload);

        EV_INFO << "Server :  Send ERS response\n";
        sendPacket(outPacket, srcAddr, srcSap);
    }
 //기존에 있던 것들.. 참고해서 작성하기
    /*
            const auto& req = msg->peekAtFront<MyEtherAppReq>();
            if (req == nullptr)
                throw cRuntimeError("data type error: not an EtherAppReq arrived in packet %s", msg->str().c_str());
            packetsReceived++;
            emit(packetReceivedSignal, msg);

            MacAddress srcAddr = msg->getTag<MacAddressInd>()->getSrcAddress();
            int srcSap = msg->getTag<Ieee802SapInd>()->getSsap();
            long requestId = req->getRequestId();
            long replyBytes = req->getResponseBytes();
            int repHello = req->getHello() + 1;

            // send back packets asked by EtherAppClient side
            for (int k = 0; replyBytes > 0; k++) {
                int l = replyBytes > MAX_REPLY_CHUNK_SIZE ? MAX_REPLY_CHUNK_SIZE : replyBytes;
                replyBytes -= l;

                std::ostringstream s;
                s << msg->getName() << "-resp-" << k;

                Packet *outPacket = new Packet(s.str().c_str(), IEEE802CTRL_DATA);
                const auto& outPayload = makeShared<MyEtherAppResp>();
                outPayload->setRequestId(requestId);
                outPayload->setChunkLength(B(l));
                outPayload->setHello(repHello);
                outPayload->addTag<CreationTimeTag>()->setCreationTime(simTime());
                outPacket->insertAtBack(outPayload);

                EV_INFO << "Send response `" << outPacket->getName() << "' to " << srcAddr << " ssap=" << localSap << " dsap=" << srcSap << " length=" << l << "B requestId=" << requestId << "\n";
                EV_INFO << "Server :  Send Hello Value : "<< outPayload->getHello()<<std::endl;
                sendPacket(outPacket, srcAddr, srcSap);
            }
    */




    //테스트로 짰던 것들...
    /*
    if(msg->getKind() == MYMSG_REQ){
        const auto& req = msg->peekAtFront<MyEtherAppReq>();
        if (req == nullptr)
            throw cRuntimeError("data type error: not an EtherAppReq arrived in packet %s", msg->str().c_str());
        packetsReceived++;
        emit(packetReceivedSignal, msg);

        MacAddress srcAddr = msg->getTag<MacAddressInd>()->getSrcAddress();
        int srcSap = msg->getTag<Ieee802SapInd>()->getSsap();
        long requestId = req->getRequestId();
        long replyBytes = req->getResponseBytes();
        int repHello = req->getHello() + 1;

        // send back packets asked by EtherAppClient side
        for (int k = 0; replyBytes > 0; k++) {
            int l = replyBytes > MAX_REPLY_CHUNK_SIZE ? MAX_REPLY_CHUNK_SIZE : replyBytes;
            replyBytes -= l;

            std::ostringstream s;
            s << "MYMSG_RESP";

            Packet *outPacket = new Packet(s.str().c_str(), IEEE802CTRL_DATA);
            const auto& outPayload = makeShared<MyEtherAppResp>();
            outPayload->setRequestId(requestId);
            outPayload->setChunkLength(B(l));
            outPayload->setHello(repHello);
            outPayload->addTag<CreationTimeTag>()->setCreationTime(simTime());
            outPacket->insertAtBack(outPayload);

            EV_INFO << "Send response `" << outPacket->getName() << "' to " << srcAddr << " ssap=" << localSap << " dsap=" << srcSap << " length=" << l << "B requestId=" << requestId << "\n";
            EV_INFO << "Server :  Send Hello Value : "<< outPayload->getHello()<<std::endl;
            sendPacket(outPacket, srcAddr, srcSap);
        }
       EV_INFO << "Server :  Send Hello Value : "<< req->getHello()<<std::endl;
    }
    else if(msg->getKind() == ES_AVAILABILITY_REQ){
        const auto& req = msg->peekAtFront<MyAvailabilityReq>();
        if (req == nullptr)
            throw cRuntimeError("data type error: not an MyAvailabilityReq arrived in packet %s", msg->str().c_str());
        packetsReceived++;
        emit(packetReceivedSignal, msg);

        MacAddress srcAddr = msg->getTag<MacAddressInd>()->getSrcAddress();
        int srcSap = msg->getTag<Ieee802SapInd>()->getSsap();

        //요청 온 RSU의 목록을 추가함.
        //Availability_RSU.insert(make_pair{})
        EV<<"Server : Availability Request received!!!!!!"<<std::endl;
        //추가동작..


        std::ostringstream s;
        s << "ES_AVAILABILITY_REQ";
        Packet *outPacket = new Packet(s.str().c_str(), IEEE802CTRL_DATA);
        const auto& outPayload = makeShared<MyAvailabilityResp>();
        outPayload->setAvailability(100);
        outPayload->setChunkLength(B(MAX_REPLY_CHUNK_SIZE));

        outPayload->addTag<CreationTimeTag>()->setCreationTime(simTime());
        outPacket->setKind(ES_AVAILABILITY_RESP);
        outPacket->insertAtBack(outPayload);


        EV_INFO << "Server :  Send Availability Value : "<< outPayload->getAvailability()<<std::endl;
        sendPacket(outPacket, srcAddr, srcSap);
    }
    else if(msg->getKind() == OFFLOADING_REQ){
        const auto& resp = msg->peekAtFront<MyOffloadingReq>();
        if (resp == nullptr)
            throw cRuntimeError("data type error: not an MyOffloadingReq arrived in packet %s", msg->str().c_str());
        packetsReceived++;
        emit(packetReceivedSignal, msg);

        MacAddress srcAddr = msg->getTag<MacAddressInd>()->getSrcAddress();
        int srcSap = msg->getTag<Ieee802SapInd>()->getSsap();


          //수정
          //int ttl = msg->getTag<CreationTTLTag>()->getTtl();
          //EV<<"Mac Relay Unit : GET TAG!!!!!!!!!!!!" << ttl <<'\n';
          //수정 끝



        //요청 온 RSU의 목록을 추가함.
        //delay.....

        EV<<"Server : MyOffloading Request received!!!!!!"<<std::endl;
        //추가동작..

        EV_INFO << "Server : received data value : " << resp->getData()<<'\n';
        EV_INFO << "Server : received Constraint value : " << resp->getConstraint()<<'\n';
        EV_INFO << "Server : received Cycle value : " << resp->getCycle()<<'\n';
        EV_INFO << "Server : received Time Tag value : " << resp->getTag<CreationTimeTag>()->getCreationTime()<<'\n';



        std::ostringstream s;
        s << "OFFLOADING_RESP";
        Packet *outPacket = new Packet(s.str().c_str(), IEEE802CTRL_DATA);
        const auto& outPayload = makeShared<MyOffloadingResp>();


        outPayload->setData(resp->getCycle()*resp->getConstraint());
        outPayload->setChunkLength(B(MAX_REPLY_CHUNK_SIZE));
        outPayload->addTag<CreationTimeTag>()->setCreationTime(simTime());
        outPacket->setKind(OFFLOADING_RESP);
        outPacket->insertAtBack(outPayload);


        EV_INFO << "Server :  Send Offloading Value : "<< outPayload->getData()<<std::endl;
        sendPacket(outPacket, srcAddr, srcSap);
    }
     */
    delete msg;
}

void ServersideApp::sendPacket(Packet *datapacket, const MacAddress& destAddr, int destSap)
{
    EV<<" Server Call sendPacket."<<std::endl;
    datapacket->addTagIfAbsent<MacAddressReq>()->setDestAddress(destAddr);
    auto ieee802SapReq = datapacket->addTagIfAbsent<Ieee802SapReq>();
    ieee802SapReq->setSsap(localSap);
    ieee802SapReq->setDsap(destSap);

    emit(packetSentSignal, datapacket);
    llcSocket.send(datapacket);
    packetsSent++;
}

void ServersideApp::registerDsap(int dsap)
{
    EV<<" Server Call registerDsap."<<std::endl;
    EV_DEBUG << getFullPath() << " registering DSAP " << dsap << "\n";

    llcSocket.open(-1, dsap);
}

void ServersideApp::finish()
{
}

} // namespace inet


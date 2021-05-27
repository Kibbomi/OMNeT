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


        //내가 추가
        remoteSap = 0xf1;

        // statistics
        packetsSent = packetsReceived = 0;

        // socket
        llcSocket.setOutputGate(gate("out"));
        llcSocket.setCallback(this);

        f = (int)ceil(uniform(1,3));
        capacity = 10;
        isAvailable = true;
        //capacity / f is limit.

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

    if(msg->isSelfMessage()){
        //작성..
        handleSelfMessage(msg);
    }
    else
       llcSocket.processMessage(msg);
    //llcSocket.processMessage(msg);
}

void ServersideApp::handleSelfMessage(cMessage* msg)
{
    if(msg->getKind() == Self_COEN)
    {
        std::string CarKey = msg->getName();

        if(Tasks.count(CarKey) != 0){

            EV<<this->getParentModule()->getFullName()<<"Send CO Resp\n";

            Packet* outPacket = new Packet("ENCOResp",IEEE802CTRL_DATA);
            const auto& outPayload = makeShared<ENCOResp>();

            outPayload->setChunkLength(B(64));
            outPayload->setTaskID(Tasks[CarKey].TaskId);
            outPayload->setCarAddr(Tasks[CarKey].CarAddr);
            outPayload->setCOResult(Tasks[CarKey].COResult);

            outPacket->insertAtBack(outPayload);

            outPacket->addTag<MacAddressReq>()->setDestAddress(Tasks[CarKey].RSUAddr);

            auto ieee802SapReq = outPacket->addTag<inet::Ieee802SapReq>();
            ieee802SapReq->setSsap(localSap);
            ieee802SapReq->setDsap(remoteSap);

            emit(packetSentSignal,outPacket);
            llcSocket.send(outPacket);

            //자료구조에서 삭제.
            Tasks.erase(CarKey);

            //if(Tasks.size() < capacity/f * 0.6){

            if(Tasks.size() == 0 ){ //test
                for(auto iter = RSUs.begin(); iter != RSUs.end(); ++iter)
                {
                    Packet *outPacket = new Packet("AvailabilityInfo",IEEE802CTRL_DATA);
                    const auto& outPayload = makeShared<AvailabilityInfo>();

                    outPayload->setChunkLength(B(64));
                    outPayload->setIsAvailable(true);
                    outPacket->insertAtBack(outPayload);

                    outPacket->addTagIfAbsent<MacAddressReq>()->setDestAddress((*iter).second.addr);
                    auto ieee802SapReq = outPacket->addTagIfAbsent<Ieee802SapReq>();
                    ieee802SapReq->setSsap(localSap);
                    ieee802SapReq->setDsap(remoteSap);

                    emit(packetSentSignal,outPacket);
                    llcSocket.send(outPacket);
                    EV<<this->getParentModule()->getFullName()<<" is available. Send a availableInfo message\n";
                }
            }
        }
    }
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
        //outPayload->setChunkLength(B(21));
        outPayload->setChunkLength(B(64));
        outPayload->setCapacity(capacity);
        outPayload->setF(f);
        outPayload->setIsAvailableEN(isAvailable);
        outPayload->setInfo(OnlyES);

        //not used
        outPayload->setY(0);
        outPayload->setX(0);
        outPayload->setCoverage(0);
        outPacket->insertAtBack(outPayload);

        EV_INFO << "Server :  Send ERS response\n";
        sendPacket(outPacket, srcAddr, srcSap);
    }
    else if(strcmp(msg->getName(),"ENCOReq") == 0)
    {
        const auto& req = msg->peekAtFront<ENCOReq>();
        if (req == nullptr)
            throw cRuntimeError("data type error: not an ENCOReq arrived in packet %s", msg->str().c_str());

        emit(packetReceivedSignal, msg);

        MacAddress srcAddr;
        if(req->getToSendRSU()== MacAddress::UNSPECIFIED_ADDRESS)
            srcAddr = msg->getTag<MacAddressInd>()->getSrcAddress();
        else
            srcAddr = req->getToSendRSU();

        EV<<"Expected RSU : "<<srcAddr.str()<<'\n';

        int srcSap = msg->getTag<Ieee802SapInd>()->getSsap();

        //Save Car EN information.
        //map..
        std::string CarKey = std::to_string(req->getCarAddr()) + std::to_string(req->getTaskID());
        //CarKey = "CarAddr + TaskID" it is unique value;

        if(Tasks.count(CarKey) == 0){
            Format_Task curTask;

            curTask.CarAddr = req->getCarAddr();
            //curTask.RSUAddr
            //도착지 RSU계산할 것.
            curTask.TaskId = req->getTaskID();
            curTask.COResult = 200;

            //여기는 예상위치 구현 시 수정.
            curTask.RSUAddr = srcAddr;


            Tasks[CarKey] = curTask;

            double processingTime = (double)req->getRequiredCycle()/(double)f;

            cMessage* self_msg = new cMessage(CarKey.c_str(),Self_COEN);
            scheduleAt(simTime() + processingTime, self_msg);    //1은 s임.
            EV<<this->getParentModule()->getFullName()<<"received ENCOReq message It will reply at "<<simTime()+processingTime<<'\n';


            //availability check

            //over the capacity
            //if( (capacity / f)*0.6 < Tasks.size())
            if(Tasks.size() == 1)   //for Test!!
            {
                for(auto iter = RSUs.begin(); iter != RSUs.end(); ++iter)
                {
                    Packet *outPacket = new Packet("AvailabilityInfo",IEEE802CTRL_DATA);
                    const auto& outPayload = makeShared<AvailabilityInfo>();

                    outPayload->setChunkLength(B(64));
                    outPayload->setIsAvailable(false);
                    outPacket->insertAtBack(outPayload);

                    outPacket->addTagIfAbsent<MacAddressReq>()->setDestAddress((*iter).second.addr);
                    auto ieee802SapReq = outPacket->addTagIfAbsent<Ieee802SapReq>();
                    ieee802SapReq->setSsap(localSap);
                    ieee802SapReq->setDsap(remoteSap);

                    emit(packetSentSignal,outPacket);
                    llcSocket.send(outPacket);
                    EV<<this->getParentModule()->getFullName()<<" is not available. Send a availableInfo message\n";
                }
            }
        }


    }

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


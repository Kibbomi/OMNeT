/*
 * Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "MyEtherAppClient.h"

#include "inet/applications/ethernet/EtherApp_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/Ieee802Ctrl.h"
#include "inet/linklayer/common/Ieee802SapTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"

namespace inet {

Define_Module(MyEtherAppClient);

MyEtherAppClient::~MyEtherAppClient()
{
    cancelAndDelete(timerMsg);
}

void MyEtherAppClient::initialize(int stage)
{
    if (stage == INITSTAGE_APPLICATION_LAYER && isGenerator())
        timerMsg = new cMessage("generateNextPacket");


    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        reqLength = &par("reqLength");
        respLength = &par("respLength");
        sendInterval = &par("sendInterval");

        localSap = par("localSAP");
        remoteSap = par("remoteSAP");

        seqNum = 0;
        WATCH(seqNum);

        // statistics
        packetsSent = packetsReceived = 0;
        WATCH(packetsSent);
        WATCH(packetsReceived);

        startTime = par("startTime");
        stopTime = par("stopTime");
        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        llcSocket.setOutputGate(gate("out"));
        llcSocket.setCallback(this);
    }
    EV<<" Client : Call Initialized."<<std::endl;
}

void MyEtherAppClient::handleMessageWhenUp(cMessage *msg)
{
    //scheduledAt하면 여기로 오지 않을까.. 올곳이 여기 밖에 없음.
    EV<<" Client : Call handleMessageWhenup."<<std::endl;
    if (msg->isSelfMessage()) {
        if (msg->getKind() == START) {
            EV_DEBUG << getFullPath() << " registering DSAP " << localSap << "\n";
            llcSocket.open(-1, localSap);

            destMacAddress = resolveDestMacAddress();
            // if no dest address given, nothing to do
            if (destMacAddress.isUnspecified())
                return;
        }

        sendPacket();
        scheduleNextPacket(false);
    }
    else
        llcSocket.processMessage(msg);
}

void MyEtherAppClient::handleStartOperation(LifecycleOperation *operation)
{
    EV<<" Client : Call handleStartOperation."<<std::endl;
    if (isGenerator())
        scheduleNextPacket(true);
    //여기서 바로 Expanding Ring Search시작하는 Message 넣으면 될 듯
}

void MyEtherAppClient::handleStopOperation(LifecycleOperation *operation)
{
    EV<<" Client : Call handleStopOperation."<<std::endl;
    cancelNextPacket();
    llcSocket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void MyEtherAppClient::handleCrashOperation(LifecycleOperation *operation)
{
    EV<<" Client : Call handleCrashOperation."<<std::endl;
    cancelNextPacket();
    if (operation->getRootModule() != getContainingNode(this))
        llcSocket.destroy();
}

void MyEtherAppClient::socketClosed(inet::Ieee8022LlcSocket *socket)
{
    EV<<" Client : Call socketClosed."<<std::endl;
    if (operationalState == State::STOPPING_OPERATION && !llcSocket.isOpen())
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

bool MyEtherAppClient::isGenerator()
{
    EV<<" Client : Call isGenerator."<<std::endl;
    return par("destAddress").stringValue()[0];
}

void MyEtherAppClient::scheduleNextPacket(bool start)
{
    EV<<" Client : Call scheduleNextPacket."<<std::endl;
    simtime_t cur = simTime();
    simtime_t next;
    if (start) {
        next = cur <= startTime ? startTime : cur;
        timerMsg->setKind(START);
    }
    else {
        //끝에 Uniform 추가함.
        next = cur + *sendInterval + uniform(0.01, 0.2);
        timerMsg->setKind(NEXT);
    }
    if (stopTime < SIMTIME_ZERO || next < stopTime)
        scheduleAt(next, timerMsg);
}

void MyEtherAppClient::cancelNextPacket()
{
    EV<<" Client : Call cancelNextPacket."<<std::endl;
    if (timerMsg)
        cancelEvent(timerMsg);
}

MacAddress MyEtherAppClient::resolveDestMacAddress()
{
    EV<<" Client : Call resolveDestMacAddress."<<std::endl;
    MacAddress destMacAddress;
    //여기서 hostname으로 구분함.
    const char *destAddress = par("destAddress");
    if (destAddress[0]) {
        if (!destMacAddress.tryParse(destAddress))
            destMacAddress = L3AddressResolver().resolve(destAddress, L3AddressResolver::ADDR_MAC).toMac();
    }
    return destMacAddress;
}

void MyEtherAppClient::sendPacket()
{
    EV<<" Client : Call sendPacket."<<std::endl;
    seqNum++;

    char msgname[30];
    sprintf(msgname, "req-%d-%ld", getId(), seqNum);
    EV_INFO << "Generating packet `" << msgname << "'\n";

    Packet *datapacket = new Packet(msgname, IEEE802CTRL_DATA);
    //const auto& data = makeShared<EtherAppReq>();
    const auto& data = makeShared<MyEtherAppReq>();

    long len = *reqLength;
    data->setChunkLength(B(len));
    data->setRequestId(seqNum);

    long respLen = *respLength;
    data->setResponseBytes(respLen);

    //추가
    data->setHello((int)uniform(10,100));

    data->addTag<CreationTimeTag>()->setCreationTime(simTime());

    datapacket->insertAtBack(data);

    //datapacket->addTag<MacAddressReq>()->setDestAddress(destMacAddress);
    //broadcasting
    datapacket->addTag<MacAddressReq>()->setDestAddress(MacAddress::BROADCAST_ADDRESS);
    auto ieee802SapReq = datapacket->addTag<Ieee802SapReq>();
    ieee802SapReq->setSsap(localSap);
    ieee802SapReq->setDsap(remoteSap);

    emit(packetSentSignal, datapacket);
    llcSocket.send(datapacket);
    packetsSent++;
}

void MyEtherAppClient::socketDataArrived(Ieee8022LlcSocket*, Packet *msg)
{
    EV<<" Client : Call socketDataArrived."<<std::endl;
    EV_INFO << "Received packet `" << msg->getName() << "'\n";

    //데이터 열기
    const auto& req = msg->peekAtFront<MyEtherAppResp>();
       if (req == nullptr)
           throw cRuntimeError("data type error: not an EtherAppReq arrived in packet %s", msg->str().c_str());

    //이거 원래 있던 것
    packetsReceived++;
    emit(packetReceivedSignal, msg);
    //여기까지
    MacAddress srcAddr = msg->getTag<MacAddressInd>()->getSrcAddress();

    EV << "Client : received from Server Hello is "<< req->getHello()<<std::endl;
    delete msg;
}

void MyEtherAppClient::finish()
{
    EV<<" Client : Call finish."<<std::endl;
    cancelAndDelete(timerMsg);
    timerMsg = nullptr;
}

} // namespace inet


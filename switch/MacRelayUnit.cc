// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//


#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/LayeredProtocolBase.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/Protocol.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/StringFormat.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "inet/linklayer/ethernet/EtherMacBase.h"
#include "inet/linklayer/ethernet/Ethernet.h"
#include "inet/linklayer/ethernet/switch/MacRelayUnit.h"

//mac����
#include "inet/applications/ethernet/MyEthernetExample/MyTTLTag_m.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcHeader_m.h"
#include "inet/applications/ethernet/MyEthernetExample/MyEtherMsg_m.h"

//ERS
#include "inet/applications/ethernet/EPS/ExpandingRingSearch_m.h"
#include "inet/applications/ethernet/EPS/findTarget.h"

namespace inet {

Define_Module(MacRelayUnit);

void MacRelayUnit::initialize(int stage)
{
    LayeredProtocolBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numProcessedFrames = numDiscardedFrames = 0;

        macTable = getModuleFromPar<IMacAddressTable>(par("macTableModule"), this);
        ifTable = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);

        WATCH(numProcessedFrames);
        WATCH(numDiscardedFrames);
    }
    else if (stage == INITSTAGE_LINK_LAYER) {
        registerService(Protocol::ethernetMac, nullptr, gate("ifIn"));
        registerProtocol(Protocol::ethernetMac, gate("ifOut"), nullptr);
    }
}

void MacRelayUnit::handleLowerPacket(Packet *packet)
{
    handleAndDispatchFrame(packet);
    updateDisplayString();
}

void MacRelayUnit::updateDisplayString() const
{
    auto text = StringFormat::formatString(par("displayStringTextFormat"), [&] (char directive) {
        static std::string result;
        switch (directive) {
            case 'p':
                result = std::to_string(numProcessedFrames);
                break;
            case 'd':
                result = std::to_string(numDiscardedFrames);
                break;
            default:
                throw cRuntimeError("Unknown directive: %c", directive);
        }
        return result.c_str();
    });
    getDisplayString().setTagArg("t", 0, text);
}

void MacRelayUnit::broadcast(Packet *packet, int arrivalInterfaceId)
{
    EV_DETAIL << "Broadcast frame " << packet << endl;

    auto oldPacketProtocolTag = packet->removeTag<PacketProtocolTag>();
    packet->clearTags();
    auto newPacketProtocolTag = packet->addTag<PacketProtocolTag>();
    *newPacketProtocolTag = *oldPacketProtocolTag;
    delete oldPacketProtocolTag;
    packet->trim();

    int numPorts = ifTable->getNumInterfaces();
    for (int i = 0; i < numPorts; i++) {
        InterfaceEntry *ie = ifTable->getInterface(i);
        if (ie->isLoopback() || !ie->isBroadcast())
            continue;
        int ifId = ie->getInterfaceId();
        if (arrivalInterfaceId != ifId) {
            Packet *dupFrame = packet->dup();
            dupFrame->addTagIfAbsent<InterfaceReq>()->setInterfaceId(ifId);
            emit(packetSentToLowerSignal, dupFrame);
            send(dupFrame, "ifOut");
        }
    }
    delete packet;
}

void MacRelayUnit::handleAndDispatchFrame(Packet *packet)
{
    //FIXME : should handle multicast mac addresses correctly

    const auto& frame = packet->peekAtFront<EthernetMacHeader>();
    int arrivalInterfaceId = packet->getTag<InterfaceInd>()->getInterfaceId();

    //����
    if(strcmp(packet->getName(),"ERSReq")==0)
    {
        //pop�� �ܼ��� iterater�� �̵���Ű�� ��.
        //const auto& EPSFrameHeader = packet->popAtFront<EthernetMacHeader>();
        //const auto& EPSLlcHeader = packet->popAtFront<Ieee8022LlcHeader>();
        //const auto& EPSData = packet->popAtFront<MyOffloadingReq>();

        //������ �����ϰ� �ٽ� �ٿ���� ��.
        const auto& ERSFrameHeader = packet->removeAtFront<EthernetMacHeader>();
        const auto& ERSLlcHeader = packet->removeAtFront<Ieee8022LlcHeader>();
        const auto& ERSData = packet->removeAtFront<ERSReq>();

        EV_INFO << "Switch : received ERS message TTL value : " << ERSData->getTTL()<<'\n';

        //discard this packet
        if(ERSData->getTTL() == 1){
            EV_INFO << "This ERS Packet has TTL value 1, discard.\n";
            delete packet;
            return ;
        }

        const auto& data = makeShared<ERSReq>();

        data->setChunkLength(B(5));
        data->setTTL(ERSData->getTTL()-1);
        data->setFindTarget(ERSData->getFindTarget());

        packet->insertAtFront(data);
        packet->insertAtFront(ERSLlcHeader);
        packet->insertAtFront(ERSFrameHeader);
    }
    //���� ��

    numProcessedFrames++;

    // update address table
    learn(frame->getSrc(), arrivalInterfaceId);

    // handle broadcast frames first
    if (frame->getDest().isBroadcast()) {
        EV << "Broadcasting broadcast frame " << frame << endl;
        broadcast(packet, arrivalInterfaceId);
        return;
    }

    // Finds output port of destination address and sends to output port
    // if not found then broadcasts to all other ports instead
    int outputInterfaceId = macTable->getInterfaceIdForAddress(frame->getDest());
    // should not send out the same frame on the same ethernet port
    // (although wireless ports are ok to receive the same message)
    if (arrivalInterfaceId == outputInterfaceId) {
        EV << "Output port is same as input port, " << packet->getFullName()
           << " dest " << frame->getDest() << ", discarding frame\n";
        numDiscardedFrames++;
        delete packet;
        return;
    }

    if (outputInterfaceId >= 0) {
        EV << "Sending frame " << frame << " with dest address " << frame->getDest() << " to port " << outputInterfaceId << endl;
        auto oldPacketProtocolTag = packet->removeTag<PacketProtocolTag>();
        packet->clearTags();
        auto newPacketProtocolTag = packet->addTag<PacketProtocolTag>();
        *newPacketProtocolTag = *oldPacketProtocolTag;
        delete oldPacketProtocolTag;
        packet->addTag<InterfaceReq>()->setInterfaceId(outputInterfaceId);
        packet->trim();
        emit(packetSentToLowerSignal, packet);
        send(packet, "ifOut");
    }
    else {
        EV << "Dest address " << frame->getDest() << " unknown, broadcasting frame " << packet << endl;
        broadcast(packet, arrivalInterfaceId);
    }
}

void MacRelayUnit::start()
{
}

void MacRelayUnit::stop()
{
}

void MacRelayUnit::learn(MacAddress srcAddr, int arrivalInterfaceId)
{
    macTable->updateTableWithAddress(arrivalInterfaceId, srcAddr);
}

void MacRelayUnit::finish()
{
    recordScalar("processed frames", numProcessedFrames);
    recordScalar("discarded frames", numDiscardedFrames);
}

} // namespace inet


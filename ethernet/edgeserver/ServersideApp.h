//
// Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
#ifndef __INET_SERVERSIDEAPP_H
//#ifndef __INET_MYETHERAPPSERVER_H
//#define __INET_MYETHERAPPSERVER_H
#define __INET_SERVERSIDEAPP_H

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/MacAddress.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcSocket.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcSocketCommand_m.h"
#include "inet/linklayer/common/Ieee802Ctrl.h"
#include "inet/linklayer/common/Ieee802Ctrl_m.h"    //Ieee802ctrl data인식 못해서 추가함.
#include "inet/linklayer/common/Ieee802SapTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"

//for message
#include "inet/applications/ethernet/MyEthernetExample/MyEtherMsg_m.h"
#include "inet/applications/ethernet/MyEthernetExample/MyEthernetMsgType.h"
#include "inet/applications/ethernet/edgeserver/EN_DataStructure.h"
#include <map>
#include <string>

//Expanding Ring Search
#include "../ERS/ExpandingRingSearch_m.h"
#include "../ERS/findTarget.h"

//Computation Offloading
#include "inet/applications/ethernet/edgeserver/ENComputationOffloading_m.h"
namespace inet {

#define MAX_REPLY_CHUNK_SIZE    1497

/**
 * including Enum values
 *  in inet namespace
 */
enum COSelfMessageType{
    Self_COEN=200
};


/**
 * Server-side process EtherAppClient.
 */
class INET_API ServersideApp : public ApplicationBase, public Ieee8022LlcSocket::ICallback
{
  protected:
    int localSap = 0;
    int remoteSap = 0;  //remoteSap은 내가 추가.. 모두 동일하게 0xf1을 쓰기 때문에 상관없을 듯.

    Ieee8022LlcSocket llcSocket;

    // statistics
    long packetsSent = 0;
    long packetsReceived = 0;


    //Availability,,, to send message to RSUs periodically
    std::map<std::string,Format_RSUCluster> RSUs;
    std::map<std::string,Format_Task> Tasks;    //string, Key is carID+taskID;
    //Offloading
    //This value can be changed by ini information, so that each server can have different value
    unsigned int f;
    unsigned int capacity;
    bool isAvailable;

    double COThreshold;

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;

    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    void registerDsap(int dsap);
    void sendPacket(Packet *datapacket, const MacAddress& destAddr, int destSap);
    virtual void socketDataArrived(Ieee8022LlcSocket*, Packet *msg) override;
    virtual void socketClosed(Ieee8022LlcSocket* socket) override;

    //for ScheduleAt
    virtual void handleSelfMessage(cMessage* msg);
};

} // namespace inet

#endif // ifndef __INET_SERVERSIDEAPP_H


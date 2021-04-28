//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#pragma once

#include "veins/modules/application/ieee80211p/MyDemoBaseApplLayer.h"


//INET Header....
//For INET message
#include "inet/common/INETDefs.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/linklayer/common/Ieee802Ctrl.h"
#include "inet/linklayer/common/Ieee802SapTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"

#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/MacAddress.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcSocket.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcSocketCommand_m.h"


//INET Messages...
#include "inet/applications/ethernet/MyEthernetExample/MyEtherMsg_m.h"
#include "inet/applications/ethernet/MyEthernetExample/MyEthernetMsgType.h"
#include "inet/applications/ethernet/MyEthernetExample/MyTTLTag_m.h"

//for self message
#include "veins/modules/application/traci/RSUCluster/SelfMessageType.h"

//Header to implement Expanding Ring Search
//to manage other ES or RSU , EPS messages
#include "inet/applications/ethernet/edgeserver/EN_DataStructure.h"
#include "inet/applications/ethernet/EPS/ExpandingRingSearch_m.h"
#include "inet/applications/ethernet/EPS/findTarget.h"
#include "inet/common/InitStages.h"
#include <map>
#include <string>

namespace veins {

/**
 * RSU using 11p and Ethernet
 */
class VEINS_API RSUClusterApp : public MyDemoBaseApplLayer, public inet::Ieee8022LlcSocket::ICallback {
//public 추가
public:
    void initialize(int stage) override;

    //for Expanding Ring Search
    int TTL_threshold = 10;
    int TTL_increasement = 2;   //const..?
    int TTL_init = 1;
    double ERS_WaitTime = 0.5;  //0.5s

    //to manage other ES/RSU
    // pair -> <Macaddress to string, information>
    std::map<std::string,inet::Format_RSUCluster> RSUs;
    std::map<std::string,inet::Format_EdgeServer> ESs;

    //Handle self Message pointer..
    cMessage* self_ptr_ERSReq = nullptr;


    //for IEEE 802.2 Llc
    int localSap = -1;
    int remoteSap = -1;
    inet::Ieee8022LlcSocket llcSocket;

    //cGate *outputgate;
    int ethIn_ID;
    int ethOut_ID;

    //ICallback abstract methods...
    virtual void socketDataArrived(inet::Ieee8022LlcSocket* socket, inet::Packet *msg) override;
    virtual void socketClosed(inet::Ieee8022LlcSocket *socket) override;


    //Message
    void handleMessage(cMessage*) override;

    //For self message
    //추가함.
    void handleSelfMsg(cMessage*) override;

    //for Expanding Ring Search
    void BeginERS(int threshold, int init);

protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;
};

} // namespace veins

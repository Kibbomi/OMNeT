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

#include "veins/modules/application/traci/MyApp/MyRSU.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

//Messaegs
#include "veins/modules/application/traci/MyApp/MyMsg_m.h"
#include "veins/modules/application/traci/MyApp/MsgOffloading_m.h"
#include "veins/modules/application/traci/MyApp/MyMsgType.h"

using namespace veins;

//Define_Module(veins::MyRSU);
Define_Module(MyRSU);

//추가
//initialize할 때 부모 클래스의 initialize실행시켜주고 하는 것 잊지말기!!!!!!!!!!!!!!!!!!!
void MyRSU::initialize(int stage)
{
    MyDemoBaseApplLayer::initialize(stage);
    if(stage == 0){
        //소프트웨어적으로 게이트를 찾는것. 물리적 연결은 ned에서 함.
        //in=findGate("in");
        //out=findGate("out");

        localSap = 0xf0;
        remoteSap = 0xf1;

        llcSocket.setOutputGate(gate("out"));
        llcSocket.setCallback(this);

        EV<<"RSU is initialized!!!!!"<<std::endl;
    }
}

void MyRSU::onWSA(DemoServiceAdvertisment* wsa)
{
    // if this RSU receives a WSA for service 42, it will tune to the chan
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

void MyRSU::onWSM(BaseFrame1609_4* frame)
{

    //MyMsg* wsm = check_and_cast<MyMsg*>(frame);
    // this rsu repeats the received traffic update in 2 seconds plus some random delay
    //sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));

    //EV<<"And My RSU ID is " << getParentModule()->getIndex()<<std::endl;

    EV<<"frame : "<<frame <<std::endl;

    cPacket* pac = frame->decapsulate();

    if(pac->getKind()==Msg_MsgOffloading){
        //802.11p Message Type

       /* MsgOffloading* msg = dynamic_cast<MsgOffloading*>(pac);

        EV<<"wsm : "<<msg<<std::endl;
        EV << "RSU : Received (X,Y) : ("<< msg->getX() << "," << msg->getY() << ")" << std::endl;

        msg->setRet(msg->getX()*msg->getY());

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->encapsulate(msg);
        populateWSM(wsm);
        //802.11p data
        sendDelayed(wsm,1,lowerLayerOut);
        */


        //Ethernet Message Type

        //잠깐만... 원래 소켓 열고 닫고 반복하면 안 좋을 것 같음. 실행시 1번 열고 종료시 닫는걸로 하자.
        llcSocket.open(-1, localSap);


        inet::Packet *datapacket = new inet::Packet("",inet::IEEE802CTRL_DATA);

        const auto& data = inet::makeShared<inet::MyEtherAppReq>();

        data->setHello(11);
        data->addTag<inet::CreationTimeTag>()->setCreationTime(simTime());

        datapacket->insertAtBack(data);
        datapacket->setName("MYMSG_REQ");



        datapacket->addTag<inet::MacAddressReq>()->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);
        EV<<"RSU send the Ethernet packet !\n";
        auto ieee802SapReq = datapacket->addTag<inet::Ieee802SapReq>();
        ieee802SapReq->setSsap(0xf0);
        ieee802SapReq->setDsap(0xf1);


        //send(datapacket,out);
        llcSocket.send(datapacket);
        EV<<"RSU send the Ethernet packet to Link!!\n";

        llcSocket.close();
        llcSocket.destroy();
    }

}

//for 802.2
void MyRSU::socketDataArrived(inet::Ieee8022LlcSocket *socket, inet::Packet *msg)
{
    EV<<" Client : Call socketDataArrived."<<std::endl;
}

void MyRSU::socketClosed(inet::Ieee8022LlcSocket *socket)
{
    EV<<" Client : Call socketClosed."<<std::endl;
    //implement a socket close method
}


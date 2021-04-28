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

#include "RSUClusterApp.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

//Messaegs
#include "veins/modules/application/traci/MyApp/MyMsg_m.h"
#include "veins/modules/application/traci/MyApp/MsgOffloading_m.h"
#include "veins/modules/application/traci/MyApp/MyMsgType.h"

#include "inet/applications/ethernet/EtherApp_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/applications/ethernet/MyEthernetExample/MyTTLTag_m.h"

using namespace veins;

Define_Module(RSUClusterApp);

//�߰�
void RSUClusterApp::initialize(int stage)
{
    //initialize function of super class
    MyDemoBaseApplLayer::initialize(stage);

    if(stage == 0){
        //EV<<"RSU call this->getParentModule()->getFullName()!! : " <<this->getParentModule()->getFullName()<<'\n';   //appl

        //����Ʈ���������� ����Ʈ�� ã�°�. ������ ������ ned���� ��.
        ethIn_ID=findGate("ethIn");
        ethOut_ID=findGate("ethOut");

        localSap = 0xf0;
        remoteSap = 0xf1;
        llcSocket.setOutputGate(gate("ethOut"));

        llcSocket.setCallback(this);
        llcSocket.open(-1, localSap);

        EV<<"RSU is initialized!!!!!"<<std::endl;
    }
    else if (stage == 1)
    {
        //������  ES�� ��� 1�� ã�Ƴ��� ��.
        EV<<"RSU call BeginERS!!\n";
        BeginERS(1, 10);
    }
}

void RSUClusterApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // if this RSU receives a WSA for service 42, it will tune to the chan
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

void RSUClusterApp::onWSM(BaseFrame1609_4* frame)
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
        inet::Packet *datapacket = new inet::Packet("",inet::IEEE802CTRL_DATA);

        const auto& data = inet::makeShared<inet::MyOffloadingReq>();

        //���� ���Ƿ� ���� size��.
        data->setChunkLength(inet::units::values::B(800));  //�����ʼ�.
        data->setConstraint(10);
        data->setCycle(1234);
        data->setData(6789);
        data->addTag<inet::CreationTimeTag>()->setCreationTime(simTime());
        EV_INFO << "RSU : Simulation Time is : "<<simTime()<<'\n';
        //�ȳ����� �� �ϻ�... �� ����?

        datapacket->insertAtBack(data);


        //ttl tag
        //datapacket->addTag<inet::CreationTTLTag>()->setTtl(3);
        datapacket->setName("OFFLOADING_REQ");




        datapacket->addTag<inet::MacAddressReq>()->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);
        EV<<"RSU send the Ethernet packet !\n";
        auto ieee802SapReq = datapacket->addTag<inet::Ieee802SapReq>();
        ieee802SapReq->setSsap(0xf0);
        ieee802SapReq->setDsap(0xf1);

        //send(datapacket,out);
        //omnetpp::emit(packetSentSignal, datapacket);
        omnetpp::cComponent::emit(inet::packetSentSignal,datapacket);
        llcSocket.send(datapacket);
        EV<<"RSU send the Ethernet packet to Link!!\n";
    }

}

//HandleMessage
void RSUClusterApp::handleMessage(cMessage* msg)
{
    EV<<"RSU Handle Message has called\n";
    if (msg->isSelfMessage()) {
            handleSelfMsg(msg);
        }
        else if (msg->getArrivalGateId() == upperLayerIn) {
            recordPacket(PassedMessage::INCOMING, PassedMessage::UPPER_DATA, msg);
            handleUpperMsg(msg);
        }
        else if (msg->getArrivalGateId() == upperControlIn) {
            recordPacket(PassedMessage::INCOMING, PassedMessage::UPPER_CONTROL, msg);
            handleUpperControl(msg);
        }
        else if (msg->getArrivalGateId() == lowerControlIn) {
            recordPacket(PassedMessage::INCOMING, PassedMessage::LOWER_CONTROL, msg);
            handleLowerControl(msg);
        }
        else if (msg->getArrivalGateId() == lowerLayerIn) {
            recordPacket(PassedMessage::INCOMING, PassedMessage::LOWER_DATA, msg);
            handleLowerMsg(msg);
        }
        else if(msg->getArrivalGateId() == ethIn_ID){   //�߰�
            EV<<"Handle Message ethIN_ID Called!!!!\n";
            //record??

            inet::Packet* Ethermsg = dynamic_cast<inet::Packet*>(msg);
            socketDataArrived(nullptr,Ethermsg);
        }
        else if(msg->getArrivalGateId() == ethOut_ID){
            EV<<"Handle Message ethOUT_ID Called!!!!\n";


        }
        else if (msg->getArrivalGateId() == -1) {
            /* Classes extending this class may not use all the gates, f.e.
             * BaseApplLayer has no upper gates. In this case all upper gate-
             * handles are initialized to -1. When getArrivalGateId() equals -1,
             * it would be wrong to forward the message to one of these gates,
             * as they actually don't exist, so raise an error instead.
             */
            throw cRuntimeError("No self message and no gateID?? Check configuration.");
        }
        else {
            /* msg->getArrivalGateId() should be valid, but it isn't recognized
             * here. This could signal the case that this class is extended
             * with extra gates, but handleMessage() isn't overridden to
             * check for the new gate(s).
             */
            throw cRuntimeError("Unknown gateID?? Check configuration or override handleMessage().");
        }
}

//override��.
void RSUClusterApp::handleSelfMsg(cMessage* msg)
{
    if(msg->getKind() == Self_ERSReq ){
            //generate Message
            //ERS Request timeout..

            //increase TTL value, and begin the ERS process.
            if(TTL_init + TTL_increasement <= TTL_threshold)
                BeginERS(TTL_init + TTL_increasement, TTL_threshold);
            else
                EV_INFO << "RSUClusterApp : TTL value exceeds the TTL_threshold value. \n";

        }
        else
        {
            //�� �Լ��� else�� Error�� ��� ������ �� �κ��� �������� �;� ��.
            MyDemoBaseApplLayer::handleSelfMsg(msg);
        }


    return;
}



//for 802.2
//This function is called when the Ethernet packet comes through wire
void RSUClusterApp::socketDataArrived(inet::Ieee8022LlcSocket *socket, inet::Packet *msg)
{
    EV<<" Client : Call socketDataArrived."<<std::endl;

    EV_INFO << "The name of received packet " << msg->getName() << "'\n";

    if(strcmp(msg->getName(),"ERSResp") == 0)
    {
        //schedule�Ǿ��ִٸ� ������ ��. �浹 ������ ���Ǵ� �� �ܷ̿�, TTL���� �̳��� ES�� ��� �� ���� ������ ����.
        if(self_ptr_ERSReq!= nullptr && self_ptr_ERSReq->isScheduled()){
            cancelAndDelete(self_ptr_ERSReq);   //cancelEvent and delete.
            self_ptr_ERSReq = nullptr;
            //cancelEvent(self_ptr_ERSReq);
        }

        const auto& resp = msg->peekAtFront<inet::ERSResp>();

        if (resp == nullptr)
           throw cRuntimeError("data type error: not an ERSResp arrived in packet %s", msg->str().c_str());


        if(resp->getInfo() == inet::OnlyES)
        {
            inet::Format_EdgeServer item = inet::Format_EdgeServer();
            item.f = resp->getF();
            item.capacity = resp->getCapacity();
            item.addr = msg->getTag<inet::MacAddressInd>()->getSrcAddress();

            //check and insert to map
            std::string key_string = item.addr.str();

            if(ESs.count(key_string) == 0)
                ESs.insert(std::make_pair(key_string,item));
            else
                EV<<"RSU : This Edge server already exist\n";

        }
        else
        {
            //RSU
            inet::Format_RSUCluster item = inet::Format_RSUCluster();

            item.y = resp->getY();
            item.x = resp->getX();
            item.coverage = resp->getCoverage();
            item.addr = msg->getTag<inet::MacAddressInd>()->getSrcAddress();

            //check and insert to map
            std::string key_string = item.addr.str();

            if(RSUs.count(key_string) == 0)
                RSUs.insert(std::make_pair(key_string,item));
        }

        EV<< "RSU updates its map table \n";
        EV<< "ES Table\n";
        for(auto iter = ESs.begin(); iter!=ESs.end(); ++iter)
            EV<<"MAC : "<<(*iter).first<<'\n';

        EV<< "RSU Table\n";
        for(auto iter = RSUs.begin(); iter!=RSUs.end(); ++iter)
            EV<<"MAC : "<<(*iter).first<<'\n';
    }

    /*if(strcmp(msg->getName(),"MYMSG_RESP")==0)
        msg->setKind(MYMSG_RESP);
    else if(strcmp(msg->getName(),"OFFLOADING_RESP")==0)
        msg->setKind(OFFLOADING_RESP);
    else if(strcmp(msg->getName(),"ES_AVAILABILITY_RESP")==0)
        msg->setKind(ES_AVAILABILITY_RESP);


    if(msg->getKind() == OFFLOADING_RESP)
    {
        const auto& req = msg->peekAtFront<inet::MyOffloadingResp>();
        if (req == nullptr)
                   throw cRuntimeError("data type error: not an MyOffloadingResp arrived in packet %s", msg->str().c_str());

        EV<<"RSU : Received MyOffloading RESP.... Data is : " <<req->getData()<<std::endl;

        MsgOffloading *offloading = new MsgOffloading();
        offloading->setRet(req->getData());
        offloading->setKind(Msg_MsgOffloading);
        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->encapsulate(offloading);
        populateWSM(wsm);

        send(wsm,lowerLayerOut);

        EV<<"RSU : Sent MyOffloading RESP.... : "<<std::endl;
    }
*/

}

void RSUClusterApp::socketClosed(inet::Ieee8022LlcSocket *socket)
{
    EV<<" Client : Call socketClosed."<<std::endl;
    //implement a socket close method
    llcSocket.close();
    llcSocket.destroy();
}

//implementation EPS
void RSUClusterApp::BeginERS(int init, int threshold){

    //to memorize state
    TTL_init = init;
    TTL_threshold = threshold;

    //Ethernet Message Type
    inet::Packet *datapacket = new inet::Packet("ERSReq",inet::IEEE802CTRL_DATA);

    const auto& data = inet::makeShared<inet::ERSReq>();
    data->setChunkLength(inet::units::values::B(5));  //unsigned int, unsigned char
    data->setTTL(init);
    data->setFindTarget(inet::RSU_ES);

    datapacket->insertAtBack(data);


    datapacket->addTag<inet::MacAddressReq>()->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);
    EV<<"RSU send the ERS Request!\n";
    auto ieee802SapReq = datapacket->addTag<inet::Ieee802SapReq>();
    ieee802SapReq->setSsap(0xf0);
    ieee802SapReq->setDsap(0xf1);

    omnetpp::cComponent::emit(inet::packetSentSignal,datapacket);
    llcSocket.send(datapacket);
    EV<<"RSU send the ERS Request to Link!!\n";

    //if ERSResp message don't come back, it will be run.
    self_ptr_ERSReq = new cMessage("",Self_ERSReq);
    scheduleAt(simTime() + ERS_WaitTime, self_ptr_ERSReq);

    return;
}


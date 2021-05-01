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
#include "veins/modules/application/traci/MyApp/MyMsg_m.h"  //체크후 삭제
#include "veins/modules/application/traci/MyApp/MsgOffloading_m.h"  //체크 후 삭제
#include "veins/modules/application/traci/MyApp/MyMsgType.h"    //체크 후 삭제


//#include "inet/applications/ethernet/EtherApp_m.h"
#include "inet/common/TimeTag_m.h"

using namespace veins;

Define_Module(RSUClusterApp);

//추가
void RSUClusterApp::initialize(int stage)
{
    //initialize function of super class
    MyDemoBaseApplLayer::initialize(stage);

    if(stage == 0){
        //EV<<"RSU call this->getParentModule()->getFullName()!! : " <<this->getParentModule()->getFullName()<<'\n';   //appl

        //소프트웨어적으로 게이트를 찾는것. 물리적 연결은 ned에서 함.
        ethIn_ID=findGate("ethIn");
        ethOut_ID=findGate("ethOut");

        localSap = 0xf1;    //0xf0
        remoteSap = 0xf1;
        llcSocket.setOutputGate(gate("ethOut"));

        llcSocket.setCallback(this);
        llcSocket.open(-1, localSap);

        myOptimalES.f = 0;
        EV<<"RSU is initialized!!!!!"<<std::endl;
    }
    else if (stage == 1)
    {
        //Expanding Ring Search..

        //사전에  ES를 적어도 1개 찾아놓을 것.
        //ERS 주석풀면 바로 시작.
       // EV<<"RSU call BeginERS!!\n";
        //BeginERS(1, 10);



        this->beaconInterval+=uniform(0.01,0.2);
        //periodical Advertisement..
        //주석 풀면 됨. 광고 이벤트 시작.

        //cMessage* selfMsg =new cMessage("",Self_RSUAdvertisement);
        //scheduleAt(simTime() + uniform(1.01, 1.2),selfMsg);

    }
}

void RSUClusterApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // if this RSU receives a WSA for service 42, it will tune to the channel
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

void RSUClusterApp::onWSM(BaseFrame1609_4* frame)
{
    // this rsu repeats the received traffic update in 2 seconds plus some random delay
    //sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));

    EV<<"frame : "<<frame <<std::endl;

    cPacket* pac = frame->decapsulate();

    if(strcmp(pac->getName(),"CarCOReq") == 0){

        CarCOReq* msg = dynamic_cast<CarCOReq*>(pac);

        //parse


        //이거는 나중에 Ethernet으로 받으면 보내면 됨. 지금은 잠깐 테스트용
        CarCOResp* resp = new CarCOResp();

        resp->setName("CarCOResp");

        resp->setCOResult(9999);
        resp->setTaskID(msg->getTaskID());

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->encapsulate(resp);
        wsm->setName("CarCOResp");
        populateWSM(wsm);
        send(wsm,lowerLayerOut);



    }


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

        //내가 임의로 정한 size임.
        data->setChunkLength(inet::units::values::B(800));  //수정필수.
        data->setConstraint(10);
        data->setCycle(1234);
        data->setData(6789);
        data->addTag<inet::CreationTimeTag>()->setCreationTime(simTime());
        EV_INFO << "RSU : Simulation Time is : "<<simTime()<<'\n';
        //안나오는 것 일뿐... 잘 동작?

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
        else if(msg->getArrivalGateId() == ethIn_ID){   //추가
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

//override함.
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
    else if(msg->getKind() == Self_RSUAdvertisement)
    {
        RSUAdvertisement* msg = new RSUAdvertisement();
        msg->setRSUName(this->getParentModule()->getFullName());
        msg->setName("RSUAdvertisement");   //속 메시지
        msg->setAdvertisementTime(simTime());
        msg->setX(curPosition.x);
        msg->setY(curPosition.y);

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->encapsulate(msg);
        wsm->setName("RSUAdvertisement");   //겉으로 보이는
        populateWSM(wsm);
        send(wsm,lowerLayerOut);

        //for next send
        cMessage* selfMsg =new cMessage("",Self_RSUAdvertisement);
        //scheduleAt(simTime() + uniform(0.01, 0.2),selfMsg);
        scheduleAt(simTime() + uniform(1, 1.2),selfMsg);
    }
    else
    {
        //이 함수에 else에 Error를 뱉기 때문에 이 부분이 마지막에 와야 됨.
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

    if(strcmp(msg->getName(), "ERSReq") == 0){

        const auto& req = msg->peekAtFront<inet::ERSReq>();
        if (req == nullptr)
           throw cRuntimeError("data type error: not an ERSReq arrived in packet %s", msg->str().c_str());

        emit(inet::packetReceivedSignal, msg);
        //Because it is RSU, so discard if msg want to find ES only
        if(req->getFindTarget()== inet::OnlyES)
        {
            delete msg;
            return;
        }

        inet::MacAddress srcAddr = msg->getTag<inet::MacAddressInd>()->getSrcAddress();
        int srcSap = msg->getTag<inet::Ieee802SapInd>()->getSsap();


        //save RSU(Master) data..
        inet::Format_RSUCluster item = inet::Format_RSUCluster();
        item.addr = srcAddr;

        std::string key_string = item.addr.str();

        if(RSUsMaster.count(key_string) == 0){
            RSUsMaster.insert(std::make_pair(key_string,item));

            EV<<this->getParentModule()->getFullName()<< " : RSU Master Table\n";
            for(auto iter = RSUsMaster.begin(); iter!=RSUsMaster.end(); ++iter)
                EV<<"MAC : "<<(*iter).first<<'\n';
        }
        else
        {
            EV<< "RSU already has this RSU, discard request.\n";
            delete msg;
            return;
        }


        //return Resp..
        inet::Packet *outPacket = new inet::Packet("ERSResp", inet::IEEE802CTRL_DATA);
        const auto& outPayload = inet::makeShared<inet::ERSResp>();

        //RSU information
        outPayload->setChunkLength(inet::units::values::B(21));
        outPayload->setY(0);    //설정하기 RSU에 맞게
        outPayload->setX(0);
        outPayload->setCoverage(10);
        outPayload->setInfo(inet::OnlyRSU);


        //not used
        outPayload->setCapacity(0);
        outPayload->setF(0);


        outPacket->insertAtBack(outPayload);

        EV_INFO << "RSU : Send ERS response\n";

        outPacket->addTagIfAbsent<inet::MacAddressReq>()->setDestAddress(srcAddr);
        auto ieee802SapReq = outPacket->addTagIfAbsent<inet::Ieee802SapReq>();
        ieee802SapReq->setSsap(localSap);
        ieee802SapReq->setDsap(srcSap);

        emit(inet::packetSentSignal,outPacket);
        llcSocket.send(outPacket);

        EV<< this->getParentModule()->getFullName()<<" updates its map table \n";
        EV<< "ES Table\n";
        for(auto iter = ESs.begin(); iter!=ESs.end(); ++iter)
            EV<<"MAC : "<<(*iter).first<<'\n';

        EV<< "RSU Master Table\n";
        for(auto iter = RSUsMaster.begin(); iter!=RSUsMaster.end(); ++iter)
            EV<<"MAC : "<<(*iter).first<<'\n';


        //send optimal RSU
        if(myOptimalES.f != 0){
            inet::Packet* outPacket_optimal = new inet::Packet("OptimalESInfo",inet::IEEE802CTRL_DATA);
            const auto& outPayload_optimal = inet::makeShared<inet::OptimalESInfo>();

            outPayload_optimal->setChunkLength(inet::units::values::B(64));
            outPayload_optimal->setESMacAddr(myOptimalES.addr);
            outPayload_optimal->setF(myOptimalES.f);

            outPacket_optimal->insertAtBack(outPayload_optimal);

            outPacket_optimal->addTagIfAbsent<inet::MacAddressReq>()->setDestAddress(srcAddr);
            auto ieee802SapReq_optimal = outPacket_optimal->addTagIfAbsent<inet::Ieee802SapReq>();
            ieee802SapReq_optimal->setSsap(localSap);
            ieee802SapReq_optimal->setDsap(srcSap);

            emit(inet::packetSentSignal,outPacket_optimal);
            llcSocket.send(outPacket_optimal);
        }


    }
    else if(strcmp(msg->getName(),"ERSResp") == 0)
    {
        //schedule되어있다면 삭제할 것. 충돌 등으로 폐기되는 것 이외로, TTL범위 이내에 ES가 없어서 안 오는 것으로 가정.
        //cancelAndDelete하면 우선, 1개 새로운것을 찾으면 멈추도록 하는 것임.
        if(self_ptr_ERSReq!= nullptr && self_ptr_ERSReq->isScheduled()){
            cancelAndDelete(self_ptr_ERSReq);   //cancelEvent and delete.
            self_ptr_ERSReq = nullptr;
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

            if(ESs.count(key_string) == 0){
                ESs.insert(std::make_pair(key_string,item));

                EV<< this->getParentModule()->getFullName()<<" updates its map table \n";
                EV<< "ES Table\n";
                for(auto iter = ESs.begin(); iter!=ESs.end(); ++iter){
                    EV<<"MAC : "<<(*iter).first<<'\n';
                    EV<<"MAC : "<<(*iter).second.f<<'\n';
                }

                //updated.. so find out new optimal ES
                FindOptimalES();
                //find myOptimalES.
            }
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

            if(RSUs.count(key_string) == 0){
                RSUs.insert(std::make_pair(key_string,item));

                EV<< this->getParentModule()->getFullName()<<" updates its map table \n";
                EV<< "RSU Table\n";
                for(auto iter = RSUs.begin(); iter!=RSUs.end(); ++iter)
                    EV<<"MAC : "<<(*iter).first<<'\n';
            }
            else
                EV<<"RSU : This RSU already exist\n";
        }
    }
    else if(strcmp(msg->getName(),"OptimalESInfo") == 0)
    {
        const auto& resp = msg->peekAtFront<inet::OptimalESInfo>();
        if (resp == nullptr)
           throw cRuntimeError("data type error: not an OptimalESInfo arrived in packet %s", msg->str().c_str());

        inet::Format_EdgeServer OptimalES;

        OptimalES.addr = resp->getESMacAddr();
        OptimalES.f = resp->getF();

        inet::MacAddress srcAddress = msg->getTag<inet::MacAddressInd>()->getSrcAddress();

        OptimalESs[srcAddress.str()] = OptimalES;

        EV<<this->getParentModule()->getFullName()<<" update my OptimalES table\n";
        for(auto iter = OptimalESs.begin(); iter != OptimalESs.end(); ++iter){
            EV<<"MAC : "<<(*iter).second.addr<<'\n';
            EV<<"f : "<<(*iter).second.f<<'\n';
        }
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
    //data->setChunkLength(inet::units::values::B(5));  //unsigned int, unsigned char
    data->setChunkLength(inet::units::values::B(64));  //unsigned int, unsigned char
    data->setTTL(init);
    data->setFindTarget(inet::RSU_ES);

    datapacket->insertAtBack(data);


    datapacket->addTag<inet::MacAddressReq>()->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);
    EV<<"RSU send the ERS Request!\n";
    auto ieee802SapReq = datapacket->addTag<inet::Ieee802SapReq>();
    //ieee802SapReq->setSsap(0xf0);
    ieee802SapReq->setSsap(localSap);
    ieee802SapReq->setDsap(remoteSap);

    omnetpp::cComponent::emit(inet::packetSentSignal,datapacket);
    llcSocket.send(datapacket);
    EV<<"RSU send the ERS Request to Link!!\n";

    //if ERSResp message don't come back, it will be run.
    self_ptr_ERSReq = new cMessage("",Self_ERSReq);
    scheduleAt(simTime() + uniform(0.01, 0.2) + ERS_WaitTime, self_ptr_ERSReq);

    return;
}

void RSUClusterApp::FindOptimalES(){
    EV<<"RSU call FindOptimalES\n";
    inet::Format_EdgeServer OptimalES;
    OptimalES.f = 0;    //기본생성자가 실행이 안 됨.   명시적 초기화.

    for(auto iter = ESs.begin(); iter!=ESs.end(); ++iter){
        if((*iter).second.capacity > 0 && OptimalES.f < (*iter).second.f)
        {
            OptimalES.addr=(*iter).second.addr;
            OptimalES.f = (*iter).second.f;
            OptimalES.capacity = (*iter).second.capacity;
        }
    }

    if(myOptimalES.f < OptimalES.f){
        myOptimalES = OptimalES;

        for(auto iter=RSUsMaster.begin(); iter!= RSUsMaster.end(); ++iter){
            //send to master RSUs

            inet::Packet  *datapacket = new inet::Packet("OptimalESInfo",inet::IEEE802CTRL_DATA);

            const auto& data = inet::makeShared<inet::OptimalESInfo>();
            data->setChunkLength(inet::units::values::B(64));  //수정?
            data->setESMacAddr(myOptimalES.addr);
            //data->setRSUMacAddr()
            data->setF(myOptimalES.f);

            datapacket->insertAtBack(data);

            datapacket->addTag<inet::MacAddressReq>()->setDestAddress((*iter).second.addr);
            auto ieee802SapReq = datapacket->addTag<inet::Ieee802SapReq>();
            ieee802SapReq->setSsap(localSap);
            ieee802SapReq->setDsap(remoteSap);

            omnetpp::cComponent::emit(inet::packetSentSignal,datapacket);
            llcSocket.send(datapacket);
        }

    }
    else if(myOptimalES.f == OptimalES.f){
        EV<<"there no reason to send Optimal packet\n";
        //nothing..
    }

    return;
}

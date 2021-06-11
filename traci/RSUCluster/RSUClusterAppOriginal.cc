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

#include "RSUClusterAppOriginal.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

//Messaegs
#include "veins/modules/application/traci/MyApp/MyMsg_m.h"  //체크후 삭제
#include "veins/modules/application/traci/MyApp/MsgOffloading_m.h"  //체크 후 삭제
#include "veins/modules/application/traci/MyApp/MyMsgType.h"    //체크 후 삭제


//#include "inet/applications/ethernet/EtherApp_m.h"
#include "inet/common/TimeTag_m.h"

using namespace veins;

Define_Module(RSUClusterAppOriginal);

//추가
void RSUClusterAppOriginal::initialize(int stage)
{
    //initialize function of super class
    MyDemoBaseApplLayer::initialize(stage);

    if(stage == 0){
        //소프트웨어적으로 게이트를 찾는것. 물리적 연결은 ned에서 함.
        ethIn_ID=findGate("ethIn");
        ethOut_ID=findGate("ethOut");

        localSap = 0xf1;    //0xf0
        remoteSap = 0xf1;
        llcSocket.setOutputGate(gate("ethOut"));

        llcSocket.setCallback(this);
        llcSocket.open(-1, localSap);

        myOptimalES.f = 0;
        //myOptimalES.isAvailable = false;
    }
    else if (stage == 1)
    {
        //Expanding Ring Search..

        //사전에  ES를 적어도 1개 찾아놓을 것.
        //ERS 주석풀면 바로 시작.
        //EV<<"RSU call BeginERS!!\n";
         BeginERS(TTL_init, TTL_threshold);


        //50ms ~ 65ms
        //this->beaconInterval+=uniform(1,1.5);
        this->beaconInterval+=uniform(0.05,0.065);


        //periodical Advertisement..
        //주석 풀면 됨. 광고 이벤트 시작. (삭제 예정)
        //cMessage* selfMsg =new cMessage("",Self_RSUAdvertisement);
        //scheduleAt(simTime() + uniform(1.01, 1.2),selfMsg);

    }
}

void RSUClusterAppOriginal::onWSA(DemoServiceAdvertisment* wsa)
{
    // if this RSU receives a WSA for service 42, it will tune to the channel
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

void RSUClusterAppOriginal::onWSM(BaseFrame1609_4* frame)
{
    // this rsu repeats the received traffic update in 2 seconds plus some random delay
    //sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));

    EV<<"frame : "<<frame <<std::endl;

    cPacket* pac = frame->decapsulate();

    if(strcmp(pac->getName(),"CarCOReq") == 0){

       /* if(myOptimalES.isAvailable == false || myOptimalES.f == 0){
            EV<<this->getParentModule()->getFullName()<<" CO is not available!\n";
            return;
        }*/


        EV<<this->getParentModule()->getFullName()<<"received CarCOReq Message!\n";
        CarCOReq* msg = dynamic_cast<CarCOReq*>(pac);

        //check constraint
        simtime_t constraintTime = msg->getReqTime() + msg->getConstraint();


        inet::ENCOReq req;
        req.setChunkLength(inet::units::values::B(88));
        req.setTaskID(msg->getTaskID());
        req.setConstraint(msg->getConstraint());
        req.setRequiredCycle(msg->getRequiredCycle());
        req.setTaskCode(msg->getTaskCode());
        req.setCarAddr(msg->getCarAddr());
        req.setCarRad(msg->getRad());
        req.setTimeLimit(constraintTime);
        req.setToSendRSU(inet::MacAddress::UNSPECIFIED_ADDRESS);

        q.push(req);

        for(auto iter = ESs.begin(); iter != ESs.end(); ++iter)
        {
            inet::Packet *outPacket = new inet::Packet("AvailabilityInfo",inet::IEEE802CTRL_DATA);
           const auto& outPayload = inet::makeShared<inet::AvailabilityInfo>();

           outPayload->setChunkLength(inet::units::values::B(88));
           outPayload->setIsAvailable(false);   //그냥

           outPacket->insertAtBack(outPayload);
           outPacket->addTag<inet::MacAddressReq>()->setDestAddress(iter->second.addr);
          auto ieee802SapReq = outPacket->addTag<inet::Ieee802SapReq>();
          ieee802SapReq->setSsap(localSap);
          ieee802SapReq->setDsap(remoteSap);

          omnetpp::cComponent::emit(inet::packetSentSignal,outPacket);
          llcSocket.send(outPacket);
        }
    }
    else if(strcmp(pac->getName(),"CARConnectionReq")==0)
    {
        EV<<this->getParentModule()->getFullName()<<"received CARConnectionReq Message!\n";

        CARConnectionReq* msg = dynamic_cast<CARConnectionReq*>(pac);
        inet::Format_Car item;
        item.CarId = msg->getCarAddr();

        if(Cars.count(item.CarId) == 0){
            Cars.insert(item.CarId);

            if(passedCars.count(item.CarId) == 1)
                passedCars.erase(item.CarId);
        }



        CARConnectionResp* resp = new CARConnectionResp();
        resp->setName("CARConnectionResp");
        resp->setRSUAddr(this->mac->getMACAddress());


        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->encapsulate(resp);
        wsm->setName("CARConnectionResp");
        populateWSM(wsm,item.CarId);
        send(wsm,lowerLayerOut);

        EV<<this->getParentModule()->getFullName()<<"Add a car\n";
        for(auto iter = Cars.begin(); iter!=Cars.end(); ++iter)
            EV<<"Now connected Cars : "<<*iter<<'\n';




    }
    else if(strcmp(pac->getName(),"CARDisconnectionReq")==0)
        {
            EV<<this->getParentModule()->getFullName()<<"received CARDisconnectionReq Message!\n";

            CARDisconnectionReq* req = dynamic_cast<CARDisconnectionReq*>(pac);

            if(Cars.count(req->getCarAddr()) == 1){
                EV<<this->getParentModule()->getFullName()<<" disconnected car : "<<req->getCarAddr()<<'\n';
                Cars.erase(req->getCarAddr());
                //self msg로 삭제 요청할 것.
                passedCars.insert(req->getCarAddr());

                //cMessage* selfMsg = new cMessage("passMsg",req->getCarAddr());
                //scheduleAt(simTime() + 7, selfMsg);
            }

            CARDisconnectionResp* resp = new CARDisconnectionResp();
            resp->setName("CARDisconnectionResp");
            resp->setRSUAddr(this->mac->getMACAddress());

            BaseFrame1609_4* wsm = new BaseFrame1609_4();
            wsm->encapsulate(resp);
            wsm->setName("CARDisconnectionResp");
            populateWSM(wsm,req->getCarAddr());
            send(wsm,lowerLayerOut);

            EV<<this->getParentModule()->getFullName()<<"Delete the Car\n";
            for(auto iter = Cars.begin(); iter!=Cars.end(); ++iter)
                EV<<"Now connected Cars : "<<*iter<<'\n';

        }
    else if(strcmp(pac->getName(),"CarCOAck") == 0)
    {
        EV<<this->getParentModule()->getFullName()<<" received CO ACK message\n";

        CarCOAck* msg = dynamic_cast<CarCOAck*>(pac);
        std::string carKey = std::to_string(msg->getCarAddr()) + std::to_string(msg->getTaskID());

        if(ACKWaitptr.count(carKey) == 1){
            if(ACKWaitptr[carKey] != nullptr && ACKWaitptr[carKey]->isScheduled())
                cancelAndDelete(ACKWaitptr[carKey]);
            ACKWaitptr.erase(carKey);
        }
    }
}

//HandleMessage
void RSUClusterAppOriginal::handleMessage(cMessage* msg)
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
void RSUClusterAppOriginal::handleSelfMsg(cMessage* msg)
{
    if(msg->getKind() == Self_ERSReq ){
        //generate Message
        //ERS Request timeout..

        //increase TTL value, and begin the ERS process.
        if(TTL_init + TTL_increasement <= TTL_threshold)
            BeginERS(TTL_init + TTL_increasement, TTL_threshold);
        else
            EV_INFO << "RSUClusterAppOriginal : TTL value exceeds the TTL_threshold value. \n";

    }
    else if(strcmp(msg->getName(),"passMsg") == 0)
    {
        EV<<this->getParentModule()->getFullName()<<" erase passed car : " <<msg->getKind()<<'\n';

        for(auto item : passedCars)
            EV<< item<<'\n';

        passedCars.erase(msg->getKind());

        EV<<this->getParentModule()->getFullName()<<" --------erased-------"<<"\n\n";
        for(auto item : passedCars)
            EV<< item<<'\n';
    }
    else if(msg->getKind() == Self_COResp){
        long carAddr = ACKWaitTasks[msg->getName()].CarAddr;
        int TaskID = ACKWaitTasks[msg->getName()].TaskId;

        //연결되어 있으면
        if(Cars.count(carAddr) == 1){
            CarCOResp* msg = new CarCOResp("CarCOResp");
            msg->setTaskID(TaskID);
            msg->setCOResult(1);    //아무거나 가능

            BaseFrame1609_4* wsm = new BaseFrame1609_4();
            wsm->encapsulate(msg);
            wsm->setName("CarCOResp");
            populateWSM(wsm, carAddr);
            send(wsm,lowerLayerOut);
            EV<<this->getParentModule()->getFullName()<<" send ENCOResp Message(Retransmit) to "<< carAddr<<'\n';
        }
        else
        {
            if(ACKWaitptr.count(msg->getName()) == 1){
                if(ACKWaitptr[msg->getName()] != nullptr && ACKWaitptr[msg->getName()]->isScheduled() )
                    cancelAndDelete(ACKWaitptr[msg->getName()]);
                ACKWaitptr.erase(msg->getName());
            }
        }
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
void RSUClusterAppOriginal::socketDataArrived(inet::Ieee8022LlcSocket *socket, inet::Packet *msg)
{
    EV<<" Client : Call socketDataArrived."<<std::endl;

    EV_INFO << "The name of received packet " << msg->getName() << "'\n";

    if(strcmp(msg->getName(), "ERSReq") == 0){

    }
    else if(strcmp(msg->getName(),"ERSResp") == 0)
    {
        const auto& resp = msg->peekAtFront<inet::ERSResp>();

        if (resp == nullptr)
           throw cRuntimeError("data type error: not an ERSResp arrived in packet %s", msg->str().c_str());


        if(resp->getInfo() == inet::OnlyES)
        {
            inet::Format_EdgeServer item = inet::Format_EdgeServer();
            item.f = resp->getF();
            item.capacity = resp->getCapacity();
            item.addr = msg->getTag<inet::MacAddressInd>()->getSrcAddress();
            item.isAvailable = resp->isAvailableEN();

            //check and insert to map
            std::string key_string = item.addr.str();

            if(ESs.count(key_string) == 0){
                ESs.insert(std::make_pair(key_string,item));

                EV<< this->getParentModule()->getFullName()<<" updates its map table \n";
                EV<< "ES Table\n";
                for(auto iter = ESs.begin(); iter!=ESs.end(); ++iter){
                    EV<<"MAC : "<<(*iter).first<<'\n';
                    EV<<"MAC : "<<(*iter).second.f<<'\n';
                    EV<<"MAC : "<<(*iter).second.isAvailable<<'\n';
                }


            }
            else
                EV<<"RSU : This Edge server already exist\n";
        }

        //delete next ERS
        //if(RSUs_left.size () != 0 && RSUs_right.size() != 0 && myOptimalES.f != 0)
            if(self_ptr_ERSReq!= nullptr && self_ptr_ERSReq->isScheduled() ){
                cancelAndDelete(self_ptr_ERSReq);   //cancelEvent and delete.
                self_ptr_ERSReq = nullptr;
                EV<< this->getParentModule()->getFullName()<<" call cancelAndDelete ERS Packet \n";
            }


    }
    else if(strcmp(msg->getName(),"OptimalESInfo") == 0)
    {

    }
    else if(strcmp(msg->getName(),"ENCOResp") == 0)
    {

        const auto& resp = msg->peekAtFront<inet::ENCOResp>();
        if (resp == nullptr)
            throw cRuntimeError("data type error: not an ENCOResp arrived in packet %s", msg->str().c_str());

        //timeover;
        if(resp->getTimeLimit() < simTime())
            return;

        //자신의 범위에 존재한다면,
        if(Cars.count(resp->getCarAddr()) == 1){
            //positive case.
            CarCOResp* ret = new CarCOResp();
            ret->setTaskID(resp->getTaskID());
            ret->setCOResult(resp->getCOResult());
            ret->setName("CarCOResp");

            BaseFrame1609_4* wsm = new BaseFrame1609_4();
            wsm->encapsulate(ret);
            wsm->setName("CarCOResp");
            populateWSM(wsm, resp->getCarAddr());
            send(wsm,lowerLayerOut);
            EV<<this->getParentModule()->getFullName()<<" send ENCOResp Message to "<< resp->getCarAddr()<<'\n';
        }
        else
        {
            return;
        }

        //for ACK;
        std::string carKey = std::to_string(resp->getCarAddr()) + std::to_string(resp->getTaskID());
        ACKWaitptr.insert(std::make_pair(carKey, new cMessage(carKey.c_str(), Self_COResp)));

        inet::Format_Task item;
        item.CarAddr = resp->getCarAddr();
        item.TaskId = resp->getTaskID();
        item.COResult = 1;  //뭐든지 OK

        ACKWaitTasks[carKey] = item;
        if(!ACKWaitptr[carKey]->isScheduled())
            scheduleAt(simTime() + CORespACKRetransmission, ACKWaitptr[carKey]);

    }
    else if(strcmp(msg->getName(),"AvailabilityInfo") == 0)
    {
        const auto& resp = msg->peekAtFront<inet::AvailabilityInfo>();
        if (resp == nullptr)
            throw cRuntimeError("data type error: not an AvailabilityInfo arrived in packet %s", msg->str().c_str());

        inet::MacAddress srcAddress = msg->getTag<inet::MacAddressInd>()->getSrcAddress();
        int srcSap = msg->getTag<inet::Ieee802SapInd>()->getSsap();
        bool doERS = true;
        if(resp->isAvailable())
        {
            doERS = false;
            if(!q.empty()){
                inet::Packet* outPacket = new inet::Packet("ENCOReq",inet::IEEE802CTRL_DATA);
                const auto& outPayload = inet::makeShared<inet::ENCOReq>();

                outPayload->setChunkLength(inet::units::values::B(88));
                outPayload->setTaskID(q.front().getTaskID());
                outPayload->setConstraint(q.front().getConstraint());
                outPayload->setRequiredCycle(q.front().getRequiredCycle());
                outPayload->setTaskCode(q.front().getTaskCode());
                outPayload->setCarAddr(q.front().getCarAddr());
                outPayload->setCarRad(q.front().getCarRad());
                outPayload->setTimeLimit(q.front().getTimeLimit());

                outPayload->setToSendRSU(inet::MacAddress::UNSPECIFIED_ADDRESS);
                q.pop();

                outPacket->insertAtBack(outPayload);

                outPacket->addTagIfAbsent<inet::MacAddressReq>()->setDestAddress(srcAddress);

                auto ieee802SapReq = outPacket->addTagIfAbsent<inet::Ieee802SapReq>();
                ieee802SapReq->setSsap(localSap);
                ieee802SapReq->setDsap(srcSap);

                emit(inet::packetSentSignal,outPacket);
                llcSocket.send(outPacket);
            }
        }
        if(doERS)
            BeginERS(TTL_init, TTL_threshold);
    }
}

void RSUClusterAppOriginal::socketClosed(inet::Ieee8022LlcSocket *socket)
{
    EV<<" Client : Call socketClosed."<<std::endl;
    //implement a socket close method
    llcSocket.close();
    llcSocket.destroy();
}

//implementation EPS
void RSUClusterAppOriginal::BeginERS(int init, int threshold){

    //to memorize state
    TTL_init = init;
    TTL_threshold = threshold;

    if(TTL_threshold < TTL_init)
        return;

    EV<<this->getParentModule()->getFullName()<<" send a ERS Req!, TTL is "<<init<<'\n';

    //Ethernet Message Type
    inet::Packet *datapacket = new inet::Packet("ERSReq",inet::IEEE802CTRL_DATA);

    const auto& data = inet::makeShared<inet::ERSReq>();
    data->setChunkLength(inet::units::values::B(88));  //unsigned int, unsigned char
    data->setTTL(init);
    data->setFindTarget(inet::RSU_ES);

    datapacket->insertAtBack(data);

    datapacket->addTag<inet::MacAddressReq>()->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);

    auto ieee802SapReq = datapacket->addTag<inet::Ieee802SapReq>();
    ieee802SapReq->setSsap(localSap);
    ieee802SapReq->setDsap(remoteSap);

    omnetpp::cComponent::emit(inet::packetSentSignal,datapacket);
    llcSocket.send(datapacket);
    EV<<"RSU send the ERS Request to Link!!\n";


    self_ptr_ERSReq = new cMessage("",Self_ERSReq);
    scheduleAt(simTime() + uniform(0.05, 0.01) + ERS_WaitTime, self_ptr_ERSReq);


    return;
}

void RSUClusterAppOriginal::FindOptimalES(){
    EV<<this->getParentModule()->getFullName()<<" call FindOptimalES\n";
    //myOptimal 갱신이 필요한 것.
    inet::Format_EdgeServer OptimalES;
    OptimalES.f = 0;    //기본생성자가 실행이 안 됨.   명시적 초기화.
    OptimalES.isAvailable = false;
    bool isMyES = false;

    //내가 찾은 것들.
    for(auto iter = ESs.begin(); iter!=ESs.end(); ++iter){
        //test
        EV<<"Iter->first "<<iter->first<<'\n';
        EV<<"iter->second.addr "<<iter->second.addr<<'\n';
        EV<<"iter->second.f "<<iter->second.f<<'\n';
        EV<<"iter->second.isAvailable "<<iter->second.isAvailable<<'\n';

        if((*iter).second.isAvailable && OptimalES.f < (*iter).second.f)
        {
            OptimalES.addr=(*iter).second.addr;
            OptimalES.f = (*iter).second.f;
            OptimalES.capacity = (*iter).second.capacity;
            OptimalES.isAvailable = iter->second.isAvailable;
            EV<<this->getParentModule()->getFullName()<<"My ES "<<(*iter).second.f<<'\n';
            isMyES=true;

        }
    }

    //cluster로부터 받는 것들.
    for(auto iter = OptimalESs.begin(); iter!=OptimalESs.end(); ++iter)
    {
        EV<<"Iter->first "<<iter->first<<'\n';
        EV<<"iter->second.addr "<<iter->second.addr<<'\n';
        EV<<"iter->second.f "<<iter->second.f<<'\n';
        EV<<"iter->second.isAvailable "<<iter->second.isAvailable<<'\n';

        if(iter->second.isAvailable && OptimalES.f < iter->second.f)
        {
            OptimalES.addr=(*iter).second.addr;
            OptimalES.f = (*iter).second.f;
            OptimalES.capacity = (*iter).second.capacity;
            OptimalES.isAvailable = iter->second.isAvailable;
            EV<<this->getParentModule()->getFullName()<<"Cluster's ES "<<(*iter).second.f<<'\n';
            isMyES=false;
        }
    }
    EV<<this->getParentModule()->getFullName()<<"FindOptimal, OptimalES.addr = "<<OptimalES.addr<<'\n';
    EV<<this->getParentModule()->getFullName()<<"FindOptimal, OptimalES.f = "<<OptimalES.f<<'\n';
    EV<<this->getParentModule()->getFullName()<<"FindOptimal, OptimalES.f = "<<OptimalES.isAvailable<<'\n';

    if(OptimalES.f == 0){
        //there is not any ES
        //so, begin ERS.
        if(TTL_init + TTL_increasement <= TTL_threshold)
            BeginERS(TTL_init + TTL_increasement, TTL_threshold);
        else
            EV_INFO << this->getParentModule()->getFullName()<< " : TTL value exceeds the TTL_threshold value. \n";

        //myOptimalES.f == 0 인 것으로 가능여부를 판단.
        myOptimalES = OptimalES;

        //새로 갱신해야함.
        //ERSresp측에서 findOptimalES를 실행해야할수도.
    }
    else {
        //최적 정보가 수정된 경우에만 Master에게 전송.
        if(myOptimalES.addr == OptimalES.addr){
            EV<<this->getParentModule()->getFullName()<<" OptimalES.addr is same myOptimalES.addr \n";
            return;
        }

        myOptimalES = OptimalES;

        // Cluster의 Optimal을 전송하면 결국 네트워크 전체를 공유하는 것과 동일해짐.
        if(!isMyES){
            EV<<this->getParentModule()->getFullName()<<"myOptimalES is not ESs .. Cluster's ES\n";
            return ;
        }

        for(auto iter=RSUsMaster.begin(); iter!= RSUsMaster.end(); ++iter){
            //send to master RSUs

            inet::Packet  *datapacket = new inet::Packet("OptimalESInfo",inet::IEEE802CTRL_DATA);

            const auto& data = inet::makeShared<inet::OptimalESInfo>();
            data->setChunkLength(inet::units::values::B(88));  //수정?
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

    EV<<"Current Optimal ES is : \n";
    EV<<"addr : "<<myOptimalES.addr<<'\n';
    EV<<"f :" <<myOptimalES.f<<'\n';

    return;
}

void RSUClusterAppOriginal::SendRSUCOLevel(bool level)
{
    //switch된 것은 호출 시 구분해서 값을 넘겨 줄 것.
    //for(long CarAddr : Cars){
    RSUCOLevel* msg = new RSUCOLevel();
    msg->setName("RSUCOLevel");
    msg->setRSUAddr(this->mac->getMACAddress());
    msg->setCOLevel(level);

    BaseFrame1609_4* wsm = new BaseFrame1609_4();
    wsm->encapsulate(msg);
    wsm->setName("RSUCOLevel");
    //populateWSM(wsm,CarAddr);
    populateWSM(wsm);   //broadcasting.. vehicle will discard this packet.
    //send(wsm,lowerLayerOut);
    sendDelayed(wsm->dup(), uniform(0.01, 0.02),lowerLayerOut);
    //}
    return;
}

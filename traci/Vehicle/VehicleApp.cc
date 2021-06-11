/*
 * VehicleApp.cc
 *
 *  Created on: 2021. 4. 28.
 *      Author: bum71
 */

#include "veins/modules/application/traci/Vehicle/VehicleApp.h"

using namespace veins;

Define_Module(veins::VehicleApp);

void VehicleApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        // Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here

        //Current connecting RSU init.
        curConnectingRSU.rssi = -987654321;
        curConnectingRSU.RSU_ID = -1;
        curConnectingRSU.COLevel = false;

        traciVehicle->setSpeed(33.3333);
        traciVehicle->setMaxSpeed(33.3333);

        //trigger
        //주석 풀면 됨.. 오프로딩 이벤트 시작.
        cMessage* self_msg = new cMessage("",Self_COReq);
        scheduleAt(simTime() + 0.5, self_msg);
    }
}

void VehicleApp::finish()
{
    DemoBaseApplLayer::finish();
    // statistics recording goes here
    int num = 0;
    for(bool item : finishedTask)
        if(item)
            ++num;

    recordScalar("finished Task",num);
    recordScalar("Tasks", finishedTask.size());

    EV<<this->getParentModule()->getFullName()<< "The number of finished task, all tasks " <<num<<"/ "<< finishedTask.size()<<'\n';
    return ;
}

void VehicleApp::onBSM(DemoSafetyMessage* bsm)
{
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here

    EV<< this->getParentModule()->getFullName()<<" received beacon message\n";
    EV<<"----------Beacon Message INFO----------\n";
    double BeaconRSSIValue = check_and_cast<DeciderResult80211*>(check_and_cast<PhyToMacControlInfo*>(bsm -> getControlInfo()) -> getDeciderResult()) -> getRecvPower_dBm();
    EV<<"Beacon Message RSSI value : "<<BeaconRSSIValue<<'\n';

    //자동완성에는 보이지 않음..
    EV<<"Sender's Mac address : "<< bsm->getSenderMacAddr()<<'\n';

    double dist = (curPosition.x - bsm->getSenderPos().x)*(curPosition.x - bsm->getSenderPos().x) + (curPosition.y - bsm->getSenderPos().y)*(curPosition.y - bsm->getSenderPos().y);
    if(dist > coverage*coverage){
        EV<< this->getParentModule()->getFullName()<<" : RSU is too far!(not in coverage)\n";
        return ;
    }


    //거리 체크

    //beacon주기가 꽤나 촘촘해야함..
    if(bsm->getSenderMacAddr() == curConnectingRSU.RSU_ID)
    {
        curConnectingRSU.rssi = BeaconRSSIValue;
        EV<<this->getParentModule()->getFullName()<<"just Updated its RSSI value\n";
    }
    else
    {
        if(curConnectingRSU.rssi < BeaconRSSIValue)
        {

            //if it is not first time,
            if(curConnectingRSU.RSU_ID != -1){
                //send disconnect message to RSU connecting to this car.

                //for retransmit
                ConnectedRSU = curConnectingRSU;

                CARDisconnectionReq* msg = new CARDisconnectionReq();
                msg->setCarAddr(this->mac->getMACAddress());
                msg->setName("CARDisconnectionReq");

                BaseFrame1609_4* wsm = new BaseFrame1609_4();
                wsm->setName("CARDisconnectionReq");
                wsm->encapsulate(msg);
                populateWSM(wsm,curConnectingRSU.RSU_ID);
                send(wsm,lowerLayerOut);

                self_ptr_Disconnect = new cMessage("",Self_Disconnect);
                scheduleAt(simTime() + 0.02, self_ptr_Disconnect);
            }

            curConnectingRSU.rssi = BeaconRSSIValue;
            curConnectingRSU.RSU_ID = bsm->getSenderMacAddr();

            CARConnectionReq* msg = new CARConnectionReq();
            msg->setCarAddr(this->mac->getMACAddress());
            msg->setRad(mobility->getHeading().getRad());
            msg->setName("CARConnectionReq");

            BaseFrame1609_4* wsm = new BaseFrame1609_4();
            wsm->setName("CARConnectionReq");
            wsm->encapsulate(msg);
            populateWSM(wsm, curConnectingRSU.RSU_ID);
            send(wsm,lowerLayerOut);

            self_ptr_Connect = new cMessage("",Self_Connect);
            scheduleAt(simTime() + 0.02, self_ptr_Connect);

            EV<<this->getParentModule()->getFullName()<<"Updated its CurConnectingRSU\n";

        }
        //if not, nothing to do.
    }
}

void VehicleApp::onWSM(BaseFrame1609_4* wsm)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples

    cPacket* pac = wsm->decapsulate();
    EV << "Car received packet named : "<< pac->getName()<<'\n';

    if(strcmp(pac->getName(), "CARConnectionResp") == 0){
        CARConnectionResp* msg = dynamic_cast<CARConnectionResp*>(pac);
        EV<<this->getParentModule()->getFullName()<<" received Connection ACK packet\n";

        if(self_ptr_Connect != nullptr && self_ptr_Connect->isScheduled()){
            cancelAndDelete(self_ptr_Connect);
        }
    }
    else if(strcmp(pac->getName(), "CARDisconnectionResp") == 0){
        //조금 동기가 안 맞을 수도 있음.
        CARDisconnectionResp* msg = dynamic_cast<CARDisconnectionResp*>(pac);
        EV<<this->getParentModule()->getFullName()<<" received Disconnection ACK packet\n";

        if(self_ptr_Disconnect != nullptr && self_ptr_Disconnect->isScheduled()){
            cancelAndDelete(self_ptr_Disconnect);

            //connected RSU 초기화..?
        }

    }
    else if(strcmp(pac->getName(), "CarCOResp") == 0){

        //수정 해야함
        CarCOResp* msg = dynamic_cast<CarCOResp*>(pac);

        EV<<"Car1 received "<<msg->getTaskID() <<" CO Resp\n";

        if(msg->getTaskID() < finishedTask.size())
            finishedTask[msg->getTaskID()]=true;

        //send ACK
        CarCOAck* ack = new CarCOAck();
        ack->setCarAddr(this->mac->getMACAddress());
        ack->setTaskID(msg->getTaskID());
        ack->setName("CarCOAck");

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->setName("CarCOAck");
        wsm->encapsulate(ack);
        populateWSM(wsm,curConnectingRSU.RSU_ID);
        send(wsm,lowerLayerOut);
    }
    else if(strcmp(pac->getName(), "RSUCOLevel") == 0){
        RSUCOLevel* msg = dynamic_cast<RSUCOLevel*>(pac);
        EV<<this->getParentModule()->getFullName()<<" received RSUCOLevel packet\n";

        if(msg->getRSUAddr() == curConnectingRSU.RSU_ID)
        {
            curConnectingRSU.COLevel = msg->getCOLevel();
            EV<<this->getParentModule()->getFullName()<<" change the COLevel to "<<msg->getCOLevel()<<'\n';
        }
        else
        {
            EV<<"Discard RSUCOLevel Packet.\n";
        }

    }
    return;
}

void VehicleApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void VehicleApp::handleSelfMsg(cMessage* msg)
{
    // this method is for self messages (mostly timers)
    // it is important to call the DemoBaseApplLayer function for BSM and WSM transmission

    if(msg->getKind() == Self_COReq ){

        /*if(!Ondemand && curConnectingRSU.COLevel == false)
        {
            cMessage* selfMsg =new cMessage("",Self_COReq);
            scheduleAt(simTime() + uniform(0.15, 0.16),selfMsg);
            //push back failed task
            finishedTask.push_back(false);
            EV<<this->getParentModule()->getFullName()<<" can't send CO Msg, current connected RSU is not available!\n";
            EV<<this->getParentModule()->getFullName()<<" is connected with "<<curConnectingRSU.RSU_ID<<'\n';
            return ;
        }*/


        CarCOReq* req = new CarCOReq();

        //car
        Coord curLocation = mobility->getPositionAt(simTime());
        req->setX(curLocation.x);
        req->setY(curLocation.y);
        req->setRad(mobility->getHeading().getRad());
        req->setSpeed(mobility->getSpeed());
        req->setCarName(this->getParentModule()->getFullName());

        //task information
        req->setTaskID(finishedTask.size());
        req->setConstraint(uniform(0.15,0.23));    //[150, 230]ms
        req->setRequiredCycle(uniform(0.6,0.8));  //[0.6, 0.8]GHz

        req->setTaskCode(1);  //byte;

        req->setReqTime(simTime());
        req->setCarAddr(this->mac->getMACAddress());
        req->setName("CarCOReq");
        //push Task
        finishedTask.push_back(false);

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->setName("CarCOReq");
        wsm->encapsulate(req);
        populateWSM(wsm,curConnectingRSU.RSU_ID);
        send(wsm,lowerLayerOut);

        //for next CO
        cMessage* selfMsg =new cMessage("",Self_COReq);
        scheduleAt(simTime() + uniform(0.15, 0.16),selfMsg);    //CO 150ms마다 발생
    }
    else if(msg->getKind() == Self_Connect)
    {
        CARConnectionReq* msg = new CARConnectionReq();
        msg->setCarAddr(this->mac->getMACAddress());
        msg->setName("CARConnectionReq");

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->setName("CARConnectionReq");
        wsm->encapsulate(msg);
        populateWSM(wsm, curConnectingRSU.RSU_ID);
        send(wsm,lowerLayerOut);

        self_ptr_Connect = new cMessage("",Self_Connect);
        scheduleAt(simTime() + 0.02, self_ptr_Connect); //20ms 연결 재전송
        EV<<this->getParentModule()->getFullName()<< "retransmit Connection Msg to "<< curConnectingRSU.RSU_ID <<'\n';
    }
    else if(msg->getKind() == Self_Disconnect)
    {
        CARDisconnectionReq* ack = new CARDisconnectionReq();
        ack->setCarAddr(this->mac->getMACAddress());
        ack->setName("CARDisconnectionReq");

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->setName("CARDisconnectionReq");
        wsm->encapsulate(ack);
        populateWSM(wsm,ConnectedRSU.RSU_ID);
        send(wsm,lowerLayerOut);

        self_ptr_Disconnect = new cMessage("",Self_Disconnect);
        scheduleAt(simTime() + 0.02, self_ptr_Disconnect);
        EV<<this->getParentModule()->getFullName()<< "retransmit DisConnection Msg to "<< curConnectingRSU.RSU_ID <<'\n';
    }
    else
    {
        //이 함수 수정하기 싫어서 여기 놔뒀음.
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void VehicleApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class

    //EV<<"Speed of "<<this->getParentModule()->getFullName()<<" : "<< mobility->getSpeed()<<'\n';
    //EV<<"Heading of "<<this->getParentModule()->getFullName()<<" : "<< mobility->getHeading()<<'\n';
    //EV<<"location of " <<this->getParentModule()->getFullName()<<" : (" <<curPosition.y<<","<<curPosition.x<<")\n";
}


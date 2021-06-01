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


        //trigger
        //주석 풀면 됨.. 오프로딩 이벤트 시작.
        cMessage* self_msg = new cMessage("",Self_COReq);
        scheduleAt(simTime() + 4, self_msg);
    }
}

void VehicleApp::finish()
{
    DemoBaseApplLayer::finish();
    // statistics recording goes here
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

                CARDisconnectionReq* msg = new CARDisconnectionReq();
                msg->setCarAddr(this->mac->getMACAddress());
                msg->setName("CARDisconnectionReq");

                BaseFrame1609_4* wsm = new BaseFrame1609_4();
                wsm->setName("CARDisconnectionReq");
                wsm->encapsulate(msg);
                populateWSM(wsm,curConnectingRSU.RSU_ID);
                send(wsm,lowerLayerOut);
        }

        curConnectingRSU.rssi = BeaconRSSIValue;
        curConnectingRSU.RSU_ID = bsm->getSenderMacAddr();

        CARConnectionReq* msg = new CARConnectionReq();
        msg->setCarAddr(this->mac->getMACAddress());
        msg->setName("CARConnectionReq");

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->setName("CARConnectionReq");
        wsm->encapsulate(msg);
        populateWSM(wsm, curConnectingRSU.RSU_ID);
        send(wsm,lowerLayerOut);

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

    if(strcmp(pac->getName(),"RSUAdvertisement") == 0)
    {
        RSUAdvertisement* msg = dynamic_cast<RSUAdvertisement*>(pac);

        if(RSUs.count(msg->getRSUName()) == 0){
            Coord curLocation = mobility->getPositionAt(simTime());
            int distance = (curLocation.x - msg->getX())*(curLocation.x - msg->getX())
                    -(curLocation.y - msg->getY())*(curLocation.y - msg->getY());

            inet::RSU_Advertisement item = inet::RSU_Advertisement();
            item.distance = distance;
            item.advertisementTime = msg->getAdvertisementTime();
            item.RSU_ID = msg->getSenderMacAddr();

            //do not sqrt, because we just compare the values..
            RSUs.insert(std::make_pair(msg->getRSUName(),item));
            EV<<"Car1 connect to new RSU\n";
        }
        else
        {
            //시간이 오래 된 애들은 여기서 순회하면서 삭제.

        }
    }
    else if(strcmp(pac->getName(), "CARConnectionResp") == 0){
        CARConnectionResp* msg = dynamic_cast<CARConnectionResp*>(pac);
        EV<<this->getParentModule()->getFullName()<<" received Connection ACK packet\n";
    }
    else if(strcmp(pac->getName(), "CARDisconnectionResp") == 0){
        CARDisconnectionResp* msg = dynamic_cast<CARDisconnectionResp*>(pac);
        EV<<this->getParentModule()->getFullName()<<" received Disconnection ACK packet\n";
    }
    else if(strcmp(pac->getName(), "CarCOResp") == 0){

        //수정 해야함
        CarCOResp* msg = dynamic_cast<CarCOResp*>(pac);

        EV<<"Car1 received "<<msg->getTaskID() <<" CO Resp\n";
        finishedTask[msg->getTaskID()]=true;
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

        if(curConnectingRSU.COLevel == false)
        {
            cMessage* selfMsg =new cMessage("",Self_COReq);
            scheduleAt(simTime() + uniform(2.01, 2.2),selfMsg);

            EV<<this->getParentModule()->getFullName()<<" can't send CO Msg, current connected RSU is not available!\n";
            return ;
        }


        CarCOReq* msg = new CarCOReq();

        Coord curLocation = mobility->getPositionAt(simTime());
        msg->setX(curLocation.x);
        msg->setY(curLocation.y);
        msg->setRad(mobility->getHeading().getRad());
        msg->setSpeed(mobility->getSpeed());
        msg->setCarName(this->getParentModule()->getFullName());

        msg->setTaskID(finishedTask.size());

        //custom value
        msg->setConstraint(2.0);
        msg->setRequiredCycle(17);  //15G cycle
        msg->setTaskCode(100);  //byte;

        msg->setReqTime(simTime());
        msg->setCarAddr(this->mac->getMACAddress());
        msg->setName("CarCOReq");
        //push Task
        finishedTask.push_back(false);

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->setName("CarCOReq");
        wsm->encapsulate(msg);
        //populateWSM(wsm);
        populateWSM(wsm,curConnectingRSU.RSU_ID);
        send(wsm,lowerLayerOut);

        //for next send
        cMessage* selfMsg =new cMessage("",Self_COReq);
        scheduleAt(simTime() + uniform(1.51, 2.0),selfMsg);
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

    //여기서 거리가 멀어짐에 따라 RSU와 연결을 맺고 안 맺고
    //EV<<"Speed of "<<this->getParentModule()->getFullName()<<" : "<< mobility->getSpeed()<<'\n';
   // EV<<"Heading of "<<this->getParentModule()->getFullName()<<" : "<< mobility->getHeading()<<'\n';
    //EV<<"location of Car1 : (" <<curPosition.y<<","<<curPosition.x<<")\n";


    //compare all of knowing RSUs
    //for(auto iter = RSUs.begin(); iter != RSUs.end(); ++iter){

    //}

}

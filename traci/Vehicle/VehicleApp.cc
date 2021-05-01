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


        //trigger
        //�ּ� Ǯ�� ��.. �����ε� �̺�Ʈ ����.
        /*cMessage* self_msg = new cMessage("",Self_COReq);
        scheduleAt(simTime() + 4, self_msg);*/
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
    EV<<"Beacon Message RSSI value : "<<check_and_cast<DeciderResult80211*>(check_and_cast<PhyToMacControlInfo*>(bsm -> getControlInfo()) -> getDeciderResult()) -> getRecvPower_dBm()<<'\n';
    //�ڵ��ϼ����� ������ ����..
    EV<<"Sender's Mac address : "<< bsm->getSenderMacAddr()<<'\n';

    EV<<"this->mac->getmacaddress :"<<this->mac->getMACAddress()<<'\n'; //L2Address(long)�ڷ�����.

    //EV<<"Beacon Message comes from : ";
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

        if(curConnectingRSU == ""){
            curConnectingRSU = msg->getRSUName();
        }

        //test
        /*EV<<"----------Ad Message INFO----------\n";
        EV<<"sender parent fullname"<<wsm->getSenderModule()->getParentModule()->getId()<<'\n';
        */


        if(RSUs.count(msg->getRSUName()) == 0){
            Coord curLocation = mobility->getPositionAt(simTime());
            int distance = (curLocation.x - msg->getX())*(curLocation.x - msg->getX())
                    -(curLocation.y - msg->getY())*(curLocation.y - msg->getY());

            inet::RSU_Advertisement item = inet::RSU_Advertisement();
            item.distance = distance;
            item.advertisementTime = msg->getAdvertisementTime();

            //do not sqrt, because we just compare the values..
            RSUs.insert(std::make_pair(msg->getRSUName(),item));
            EV<<"Car1 connect to new RSU\n";
        }
        else
        {
            //�ð��� ���� �� �ֵ��� ���⼭ ��ȸ�ϸ鼭 ����.

        }
    }
    else if(strcmp(pac->getName(), "CarCOResp") == 0){

        //���� �ؾ���
        CarCOResp* msg = dynamic_cast<CarCOResp*>(pac);

        EV<<"Car1 received "<<msg->getTaskID() <<" CO Resp\n";
        finishedTask[msg->getTaskID()]=true;
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

        CarCOReq* msg = new CarCOReq();

        Coord curLocation = mobility->getPositionAt(simTime());
        msg->setX(curLocation.x);
        msg->setY(curLocation.y);
        //msg->setDirection(curLocation.)
        msg->setSpeed(mobility->getSpeed());
        msg->setCarName(this->getParentModule()->getFullName());

        msg->setTaskID(finishedTask.size());

        //custom value
        msg->setConstraint(2.0);
        msg->setRequiredCycle(10000);
        msg->setTaskCode(100);  //byte;

        msg->setReqTime(simTime());
        msg->setName("CarCOReq");
        //push Task
        finishedTask.push_back(false);

        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->setName("CarCOReq");
        wsm->encapsulate(msg);
        populateWSM(wsm);
        send(wsm,lowerLayerOut);

        //for next send
        cMessage* selfMsg =new cMessage("",Self_COReq);
        scheduleAt(simTime() + uniform(2.01, 3.2),selfMsg);
    }
    else
    {
        //�� �Լ� �����ϱ� �Ⱦ ���� ������.
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void VehicleApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class

    //���⼭ �Ÿ��� �־����� ���� RSU�� ������ �ΰ� �� �ΰ�
    //EV<<"Speed of Car1 : " << mobility->getSpeed()<<'\n';
    //Coord cur = mobility->getPositionAt(simTime());
    //EV<<"location of Car1 : (" <<cur.y<<","<<cur.x<<")\n";

    //compare all of knowing RSUs
    //for(auto iter = RSUs.begin(); iter != RSUs.end(); ++iter){

    //}

}

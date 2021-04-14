/*
 * MyApp.cc
 *
 *  Created on: 2021. 4. 2.
 *      Author: bum71
 */

#include "veins/modules/application/traci/MyApp/MyApp.h"

using namespace veins;

Define_Module(veins::MyApp);

void MyApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        // Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here

        cMessage* msg = new cMessage();
        msg->setKind(Msg_MsgOffloading);
        EV<<"I schedule at.."<<std::endl;
        scheduleAt(simTime() + 4, msg);
    }
}

void MyApp::finish()
{
    DemoBaseApplLayer::finish();
    // statistics recording goes here
}

void MyApp::onBSM(DemoSafetyMessage* bsm)
{
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
/*
    if(gogo==false){
        traciVehicle->setSpeedMode(0x1f);
        traciVehicle->setSpeed(0);
        gogo=true;
    }
    else
    {
        traciVehicle->setSpeedMode(0x1f);
        traciVehicle->setSpeed(10);
        gogo=false;
    }

    EV<<"I RECEIVED, My gogo value is "<< gogo <<std::endl;

    MyMsg *msg = new MyMsg();
    msg->setHello(false);
    BaseFrame1609_4* wsm = new BaseFrame1609_4();
    wsm->encapsulate(msg);
    populateWSM(wsm);
    send(wsm,lowerLayerOut);

    EV<<"Sent!!!"<<std::endl;
    */


    //send direct test
    /*
    EV << bsm->getSenderModule()<<std::endl;

    MsgOffloading *msg = new MsgOffloading();
       msg->setX(11);
       msg->setY(12);
       BaseFrame1609_4* wsm = new BaseFrame1609_4();
       wsm->encapsulate(msg);
       populateWSM(wsm);
       sendDirect(wsm,bsm->getSenderModule(),lowerLayerOut);
       */
}

void MyApp::onWSM(BaseFrame1609_4* wsm)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples

    cPacket* pac = wsm->decapsulate();
    MsgOffloading *msg = dynamic_cast<MsgOffloading *>(pac);

    EV << "Offloading Result is : " << msg->getRet()<<std::endl;
}

void MyApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyApp::handleSelfMsg(cMessage* msg)
{
     DemoBaseApplLayer::handleSelfMsg(msg);
    // this method is for self messages (mostly timers)
    // it is important to call the DemoBaseApplLayer function for BSM and WSM transmission

    if(msg->getKind() == Msg_MsgOffloading ){   //getkind말고 int값으로 정의하는게 더 좋을 듯.

        //random 모듈 계속 만들면 속도 매우 느림.. 미리 만들어 늫은거 계속 쓸 것. static으로..
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1,100);

        MsgOffloading *offloading = new MsgOffloading();
        offloading->setX(dist(gen));
        offloading->setY(dist(gen));
        offloading->setKind(Msg_MsgOffloading);
        BaseFrame1609_4* wsm = new BaseFrame1609_4();
        wsm->encapsulate(offloading);
        populateWSM(wsm);

        send(wsm,lowerLayerOut);
        //EV<<"And My ID is " << getParentModule()->getIndex()<<std::endl;
        cMessage* pac_schedule = new cMessage();
        pac_schedule ->setKind(Msg_MsgOffloading);
        scheduleAt(simTime()+ 2 + uniform(0.01, 0.2),pac_schedule);
        EV<<"CAR : Sent data is ("<<offloading->getX()<<","<<offloading->getY()<<")"<<std::endl;

    }
}

void MyApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class
}

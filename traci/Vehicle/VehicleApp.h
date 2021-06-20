/*
 * MyApp.h
 *
 *  Created on: 2021. 4. 2.
 *      Author: bum71
 */

#ifndef VEHICLEAPP_H_
#define VEHICLEAPP_H_

#include "veins/veins.h"

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
//#include "veins/modules/application/ieee80211p/VehicleBaseAppLayer.h"

//Messages
#include "veins/modules/application/traci/MyApp/MyMsg_m.h"  //삭제 예정
#include "veins/modules/application/traci/MyApp/MsgOffloading_m.h"  //삭제 예정
#include "veins/modules/application/traci/MyApp/MyMsgType.h"    //삭제 예정

#include "veins/modules/application/traci/RSUCluster/SelfMessageType.h"

//for file
#include <fstream>

//to manage connecting RSU
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include "veins/modules/application/traci/RSUCluster/RSUConnection_m.h"
#include "inet/applications/ethernet/edgeserver/EN_DataStructure.h"

//for offloading
#include "veins/modules/application/traci/RSUCluster/CarComputationOffloading_m.h"

//for RSSI & beacon
#include "veins/modules/phy/DeciderResult80211.h"
#include "veins/base/phyLayer/PhyToMacControlInfo.h"
#include "veins/modules/messages/DemoSafetyMessage_m.h"
#include "veins/modules/application/traci/RSUCluster/RSUClusterApp.h"

using namespace omnetpp;

namespace veins {

constexpr double coverage = 500;
constexpr double COTime = 0.15;
constexpr double COSize = 481;
std::string fileName = "File_set";  //test file name
int fileNumber =1;

//constexpr double COTime = 1.5;


class VEINS_API VehicleApp : public DemoBaseApplLayer {
public:

    unsigned int  COMessages = 0;

    inet::RSU_INFO curConnectingRSU;
    inet::RSU_INFO ConnectedRSU;

    std::map<std::string,inet::RSU_Advertisement> RSUs; // not overflow,,, int.. -> long long   //삭제 예정 beacon으로 구현했음.

    std::vector<std::pair<double, double>> taskInfo;    //constraint, required cycle
    std::vector<bool> finishedTask; //이름 isfinished_Task로 바꾸기

    //연결 관련
    cMessage* self_ptr_Connect = nullptr;
    cMessage* self_ptr_Disconnect = nullptr;
    //CO ACK
    cMessage* self_ptr_COAck = nullptr;

    void initialize(int stage) override;
    void finish() override;

protected:
    void onBSM(DemoSafetyMessage* bsm) override;
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;

};

}
#endif /* VehicleApp */

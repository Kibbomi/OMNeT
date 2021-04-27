/*
 * MyApp.h
 *
 *  Created on: 2021. 4. 2.
 *      Author: bum71
 */

#ifndef MYAPP_H_
#define MYAPP_H_

#include "veins/veins.h"

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

//for random
#include <random>

//Messages
#include "veins/modules/application/traci/MyApp/MyMsg_m.h"
#include "veins/modules/application/traci/MyApp/MsgOffloading_m.h"
#include "veins/modules/application/traci/MyApp/MyMsgType.h"

using namespace omnetpp;

namespace veins {

/**
 * @brief
 * This is a stub for a typical Veins application layer.
 * Most common functions are overloaded.
 * See MyVeinsApp.cc for hints
 *
 * @author David Eckhoff
 *
 */

class VEINS_API MyApp : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;
    void finish() override;


    std::random_device rd;

protected:
    void onBSM(DemoSafetyMessage* bsm) override;
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;

};

}
#endif /* MYAPP_H_ */

/*
 * EN_DataStructure.h
 *
 *  Created on: 2021. 4. 27.
 *      Author: bum71
 */

#ifndef INET_APPLICATIONS_ETHERNET_EDGESERVER_EN_DATASTRUCTURE_H_
#define INET_APPLICATIONS_ETHERNET_EDGESERVER_EN_DATASTRUCTURE_H_

#include "inet/linklayer/common/MacAddress.h"   //for eth macaddress
//#include "veins/base/utils/SimpleAddress.h"
#include <string>

namespace inet{
class Format_RSUCluster{

    //there isn't getter/setter
    public:
        inet::MacAddress addr;
        int y;
        int x;
        int coverage;
};

class Format_EdgeServer{

    public:
        inet::MacAddress addr;
        unsigned int f;
        unsigned int capacity;  //availability
        //availability 삭제 후 True로 관리하면 될듯.
        //capacity는 Edge server의 멤버변수로 삽입하면 될 듯.
        //availability 구현할 때 처리.
};

class Format_Car{
    public:
        std:: string CarName;   //이거는 필요없을 것 같은데
        long CarId;
};

class Format_Task{
    public:
        long CarAddr;
        inet::MacAddress RSUAddr;//dest
        int TaskId;
        int COResult;

};

class RSU_Advertisement{
    public:
        int distance;   //long long..
        simtime_t   advertisementTime;
        long RSU_ID;
};

class RSU_INFO{
    public:
        double rssi;
        long RSU_ID;
};

}
#endif /* INET_APPLICATIONS_ETHERNET_EDGESERVER_EN_DATASTRUCTURE_H_ */

/*
 * EN_DataStructure.h
 *
 *  Created on: 2021. 4. 27.
 *      Author: bum71
 */

#ifndef INET_APPLICATIONS_ETHERNET_EDGESERVER_EN_DATASTRUCTURE_H_
#define INET_APPLICATIONS_ETHERNET_EDGESERVER_EN_DATASTRUCTURE_H_

#include "inet/linklayer/common/MacAddress.h"

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
        unsigned int capacity;
};

}
#endif /* INET_APPLICATIONS_ETHERNET_EDGESERVER_EN_DATASTRUCTURE_H_ */

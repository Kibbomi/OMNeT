/*
 * findTarget.h
 *
 *  Created on: 2021. 4. 27.
 *      Author: bum71
 */

#ifndef INET_APPLICATIONS_ETHERNET_EPS_FINDTARGET_H_
#define INET_APPLICATIONS_ETHERNET_EPS_FINDTARGET_H_

namespace inet{
    enum Targets{
        OnlyRSU = 100,
        OnlyES,
        RSU_ES
    };
}

#endif /* INET_APPLICATIONS_ETHERNET_EPS_FINDTARGET_H_ */

/*
 * SelfMessageType.h
 *
 *  Created on: 2021. 4. 28.
 *      Author: bum71
 */

#ifndef SRC_VEINS_MODULES_APPLICATION_TRACI_RSUCLUSTER_SELFMESSAGETYPE_H_
#define SRC_VEINS_MODULES_APPLICATION_TRACI_RSUCLUSTER_SELFMESSAGETYPE_H_


enum SelfMessageType{
    Self_ERSReq = 200,
    Self_ERSResp,
    Self_RSUAdvertisement,
    Self_COReq,
    Self_Connect,
    Self_Disconnect,
    Self_COResp,
    Self_queuing
};


#endif /* SRC_VEINS_MODULES_APPLICATION_TRACI_RSUCLUSTER_SELFMESSAGETYPE_H_ */

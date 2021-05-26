//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//


cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/utility/Consts80211p.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"
}};

namespace veins;

class BaseFrame1609_4;
class noncobject Coord;
class LAddress::L2Type extends void;


packet CarCOReq extends BaseFrame1609_4 
{
    //Car information
    double x;
    double y;
    double rad;	//direction
    double speed;
    string carName;
    LAddress::L2Type CarAddr;
    
    //Task information
    int taskID;
    double constraint;
    int requiredCycle;
    int taskCode;
    
    //Packet information
    simtime_t	reqTime;
    
}

packet CarCOResp extends BaseFrame1609_4
{
    int taskID;
    int COResult;
}
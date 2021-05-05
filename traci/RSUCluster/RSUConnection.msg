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
#include <string>
}};

namespace veins;

class BaseFrame1609_4;
class noncobject Coord;

//for Beacon Message
class LAddress::L2Type extends void;

packet RSUAdvertisement extends BaseFrame1609_4 
{
    //SYN
    string RSUName;
    int y;
    int x;
    LAddress::L2Type senderMacAddr;
    
    //Time
    simtime_t	advertisementTime;
}

//Beacon message of RSU is SYN message.

packet CARConnectionReq extends BaseFrame1609_4
{
    //SYN + ACK
    string CarName;
    LAddress::L2Type CarAddr;	//car ID..
}

packet CARConnectionResp extends BaseFrame1609_4
{
    //ACK
    LAddress::L2Type RSUAddr;
    bool success;
}

packet CARDisconnectionReq extends BaseFrame1609_4
{
    //FIN
    string CarName;
    LAddress::L2Type CarAddr;
}

packet CARDisconnectionResp extends BaseFrame1609_4
{
    //FIN ACK
    string RSUName;	//이거 없어도 될 것 같음.
    LAddress::L2Type RSUAddr;
}

packet RSUBeacon extends BaseFrame1609_4
{
    //new, I added
    LAddress::L2Type senderMacAddr;
    
    //for legacy.. 
    Coord senderPos;
    Coord senderSpeed;
}


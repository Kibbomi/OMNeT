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

import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;
import inet.linklayer.common.MacAddress;

namespace inet;


class ENCOReq extends FieldsChunk
{
   //Task Information
   int taskID;
   double constraint;
   double requiredCycle;
   int taskCode;	//필요 없을 것 같음.Code는..	이미 시간에 반영..
   
   long CarAddr;	//MacAddress임.
   double CarRad;
   MacAddress toSendRSU;
   simtime_t timeLimit;
}

class ENCOResp extends FieldsChunk
{
    int taskID;
    int COResult;
    long CarAddr;
    double CarRad;
    simtime_t timeLimit;
}

class OptimalESInfo extends FieldsChunk
{
    MacAddress ESMacAddr;
    MacAddress RSUMacAddr;
    int f;
    bool isAvailable;	//f 가 0이면 false 아니면 true로 간접적으로 표현 가능할 듯.
}

class AvailabilityInfo extends FieldsChunk
{
    //Mac주소는 송신자 Tag에서 구할 수 있음..
    bool isAvailable;
}
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

namespace inet;


//
// Request packet sent by ~EtherAppClient. Contains the number of bytes to be
// sent back as response; if this value is greater than ~1400, the reply
// will consist of several Ethernet frames. See also ~EtherAppResp.
//
class MyEtherAppReq extends FieldsChunk
{
    long requestId;
    long responseBytes;
    int hello;
}

//
// Packet sent back by ~EtherAppServer in response to an ~EtherAppReq.
//
class MyEtherAppResp extends FieldsChunk
{
    int requestId;
    int numFrames;
    int hello;
}


class MyOffloadingReq extends FieldsChunk
{
    int data;
    int cycle;
    int constraint;
}

class MyOffloadingResp extends FieldsChunk
{
    int data;
}

class MyAvailabilityReq extends FieldsChunk
{
	bool flag;
}

class MyAvailabilityResp extends FieldsChunk
{
	int availability;
	//float or double 
}
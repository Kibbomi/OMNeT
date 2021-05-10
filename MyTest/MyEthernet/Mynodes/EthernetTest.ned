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

package Mynodes;

import inet.common.misc.ThruputMeteringChannel;
import inet.linklayer.ethernet.EtherBus;
//import inet.linklayer.ethernet.EtherHub;
import inet.applications.ethernet.MyEthernetExample.MyEtherHost;
import inet.node.ethernet.EtherSwitch;
import ned.DatarateChannel;


network EthernetTest
{
    @display("bgb=588,353");
    types:
        channel C extends DatarateChannel
        {
            delay = 0.1us;
            datarate = 100Mbps;
        }
    submodules:
        hostA: MyEtherHost {
            parameters:
                @display("p=159,238");
        }
        hostB: MyEtherHost {
            parameters:
                @display("p=425,238");
        }

        hostC: MyEtherHost {
            @display("p=285,52");
        }
       // etherHub: EtherHub {
       //     parameters:
       //     	@display("p=285,158");
        //    gates:
        //        ethg[3];
       // }
        etherSwitch: EtherSwitch {
            parameters:
            	@display("p=273,157");
            gates:
                ethg[3];
        }
    connections:
        etherSwitch.ethg[0] <--> C <--> hostA.ethg;
        etherSwitch.ethg[1] <--> C <--> hostB.ethg;
        etherSwitch.ethg[2] <--> C <--> hostC.ethg;
}

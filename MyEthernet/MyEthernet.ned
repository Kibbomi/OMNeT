//
// Copyright (C) 2017 Christoph Sommer <sommer@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

//import Mynodes.MyRSU_EN;
import org.car2x.veins.nodes.RSU_cluster;
//import inet.applications.ethernet.MyEthernetExample.MyEtherHost;
import inet.applications.ethernet.edgeserver.EdgeServer;
import inet.linklayer.ethernet.EtherBus;

import inet.node.ethernet.EtherHost;
import inet.node.ethernet.EtherHost2;
import inet.node.ethernet.EtherSwitch;
import org.car2x.veins.nodes.Scenario;
import ned.DatarateChannel;

network MyEthernet extends Scenario
{
    @display("bgb=2500,2500");
    types:
        channel C extends DatarateChannel
        {
            delay = 0.1us;
            datarate = 100Mbps;
        }
    submodules:
        rsu[3]: RSU_cluster;

        hostA: EdgeServer {
            @display("p=39,341");
        }
        hostB: EdgeServer {
            @display("p=161,367");
        }
        hostC: EdgeServer {
            @display("p=512,359");
        }
        switch1: EtherSwitch {
            parameters:
                @display("p=100,228");
            gates:
                ethg[3];
        }
        switch2: EtherSwitch {
            parameters:
                @display("p=226,280");

            gates:
                ethg[3];	//According to increase Edge Server or RSU, It is okay to adjust just array index.
        }
        switch3: EtherSwitch {
            parameters:
                @display("p=367,254");
            gates:
                ethg[3];
        }
        switch4: EtherSwitch {
            parameters:
                @display("p=483,270");
            gates:
                ethg[3];
        }
    connections:
        rsu[0].ethg <--> C <--> switch1.ethg[0];
        hostA.ethg <--> C <--> switch1.ethg[1];
        switch1.ethg[2] <--> C <--> switch2.ethg[0];
        hostB.ethg <--> C <--> switch2.ethg[1];
        switch2.ethg[2] <--> C <--> switch3.ethg[0];
        rsu[1].ethg <--> C <--> switch3.ethg[1];
        switch4.ethg[1] <--> C <--> switch3.ethg[2];
        rsu[2].ethg <--> C <--> switch4.ethg[0];
        hostC.ethg <--> C <--> switch4.ethg[2];


        //rsu[0].ethg <--> C <--> etherSwitch.ethg[0];
        //rsu[1].ethg <--> C <--> etherSwitch.ethg[3];
        //etherSwitch.ethg[1] <--> C <--> hostA.ethg;
        //etherSwitch.ethg[2] <--> C <--> hostB.ethg;
}

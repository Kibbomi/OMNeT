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

network TestNetwork extends Scenario
{
    @display("bgb=2500,2500");
    types:
        channel C extends DatarateChannel
        {
            delay = 0.1us;
            datarate = 100Mbps;
        }
    submodules:
        rsu[5]: RSU_cluster {
            @display("p=619.33264,148.16571");
        }
        ES1: EdgeServer {
            @display("p=88.89942,660.81903");
        }
        ES2: EdgeServer {
            @display("p=290.4048,660.81903");
        }
        ES3: EdgeServer {
            @display("p=1217.9221,660.81903");
        }
        ES4: EdgeServer {
            @display("p=1650.5659,503.7634");
        }
        switch1: EtherSwitch {
            parameters:
                @display("p=174.83553,293.3681");
            gates:
                ethg[3];
        }
        switch2: EtherSwitch {
            parameters:
                @display("p=174.83553,483.0202");

            gates:
                ethg[3];	//According to increase Edge Server or RSU, It is okay to adjust just array index.
        }
        switch3: EtherSwitch {
            parameters:
                @display("p=388.19415,293.3681");
            gates:
                ethg[2];
        }
        switch4: EtherSwitch {
            parameters:
                @display("p=734.9019,370.41425");
            gates:
                ethg[3];
        }

        switch5: EtherSwitch {
            parameters:
                @display("p=1031.2333,367.45096");
            gates:
                ethg[3];
        }
        switch6: EtherSwitch {
            parameters:
                @display("p=1262.3718,462.277");
            gates:
                ethg[3];
        }
        switch7: EtherSwitch {
            parameters:
                @display("p=1490.547,343.74445");
            gates:
                ethg[4];
        }
    connections:
        rsu[0].ethg <--> C <--> switch1.ethg[0];
        switch1.ethg[1] <--> C <--> switch2.ethg[0];
        ES1.ethg <--> C <--> switch2.ethg[1];
        ES2.ethg <--> C <--> switch2.ethg[2];
        switch1.ethg[2] <--> C <--> switch3.ethg[0];
        switch3.ethg[1] <--> C <--> switch4.ethg[0];
        rsu[1].ethg <--> C <--> switch4.ethg[1];
        switch4.ethg[2] <--> C <--> switch5.ethg[0];
        rsu[2].ethg <--> C <--> switch5.ethg[1];
        switch5.ethg[2] <--> C <--> switch6.ethg[0];
        ES3.ethg <--> C <--> switch6.ethg[1];
        switch6.ethg[2] <--> C <--> switch7.ethg[0];
        switch7.ethg[1] <--> C <--> rsu[3].ethg;
        switch7.ethg[2] <--> C <--> rsu[4].ethg;
        switch7.ethg[3] <--> C <--> ES4.ethg;


}

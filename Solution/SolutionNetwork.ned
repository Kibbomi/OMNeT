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

network SolutionNetwork extends Scenario
{
    @display("bgb=2600,2500");
    types:
        channel C2 extends DatarateChannel
        {
            //delay = 1.75ms;
            delay = 1.00ms;
            datarate = 100Mbps;
        }
        channel C4 extends DatarateChannel
        {
            delay = 3.00ms;
            datarate = 100Mbps;
        }
    submodules:
        rsu[5]: RSU_cluster {
            @display("p=250.0,100.0");
        }
        ES0: EdgeServer {
            @display("p=97.78937,693.41547");
        }
        ES1: EdgeServer {
            @display("p=444.4971,933.4439");
        }
        ES2: EdgeServer {
            @display("p=888.9942,776.3883");
        }
        ES3: EdgeServer {
            @display("p=1739.4653,776.3883");
        }
        ES4: EdgeServer {
            @display("p=2056.54,1066.7931");
        }
        ES5: EdgeServer {
            @display("p=2237.3022,1066.7931");
        }
        ES6: EdgeServer {
            @display("p=2423.991,1066.7931");
        }
        ES7: EdgeServer {
            @display("p=2468.4407,521.5433");
        }
        switch1: EtherSwitch {
            parameters:
                @display("p=248.91838,290.4048");
            gates:
                ethg[3];
        }
        switch2: EtherSwitch {
            parameters:
                @display("p=174.83553,462.277");
            gates:
                ethg[2];	//According to increase Edge Server or RSU, It is okay to adjust just array index.
        }
        switch3: EtherSwitch {
            parameters:
                @display("p=444.4971,420.7906");
            gates:
                ethg[3];
        }
        switch4: EtherSwitch {
            parameters:
                @display("p=444.4971,640.07587");
            gates:
                ethg[2];
        }
        switch5: EtherSwitch {
            parameters:
                @display("p=702.3054,290.4048");
            gates:
                ethg[3];
        }
        switch6: EtherSwitch {
            parameters:
                @display("p=1146.8025,290.4048");
            gates:
                ethg[4];
        }
        switch7: EtherSwitch {
            parameters:
                @display("p=888.9942,500.80008");
            gates:
                ethg[2];
        }
        switch8: EtherSwitch {
            parameters:
                @display("p=1348.3079,500.80008");
            gates:
                ethg[2];
        }
        switch9: EtherSwitch {
            parameters:
                @display("p=1534.9967,500.80008");
            gates:
                ethg[2];
        }
        switch10: EtherSwitch {
            parameters:
                @display("p=1689.089,290.4048");
            gates:
                ethg[5];
        }
        switch11: EtherSwitch {
            parameters:
                @display("p=1739.4653,577.84625");
            gates:
                ethg[2];
        }
        switch12: EtherSwitch {
            parameters:
                @display("p=1940.9707,500.80008");
            gates:
                ethg[2];
        }
        switch13: EtherSwitch {
            parameters:
                @display("p=2056.54,773.425");
            gates:
                ethg[3];
        }
        switch14: EtherSwitch {
            parameters:
                @display("p=2237.3022,773.425");
            gates:
                ethg[2];
        }
        switch15: EtherSwitch {
            parameters:
                @display("p=2195.8157,290.4048");
            gates:
                ethg[4];
        }
        switch16: EtherSwitch {
            parameters:
                @display("p=2423.991,773.425");
            gates:
                ethg[2];
        }
        switch17: EtherSwitch {
            parameters:
                @display("p=1899.4844,367.45096");
            gates:
                ethg[2];
        }
        switch18: EtherSwitch {
            parameters:
                @display("p=2056.54,367.45096");
            gates:
                ethg[2];
        }

    connections:
        switch1.ethg[0] <--> C2 <--> rsu[0].ethg;
        switch1.ethg[1] <--> C2 <--> switch2.ethg[0];
        switch1.ethg[2] <--> C2 <--> switch3.ethg[0];

        switch2.ethg[1] <--> C2 <--> ES0.ethg;

        switch3.ethg[1] <--> C2 <--> switch4.ethg[0];
        switch3.ethg[2] <--> C2 <--> switch5.ethg[1];

        switch4.ethg[1] <--> C2 <--> ES1.ethg;

        switch5.ethg[0] <--> C2 <--> rsu[1].ethg;
        switch5.ethg[2] <--> C2 <--> switch6.ethg[1];

        switch6.ethg[0] <--> C2 <--> rsu[2].ethg;
        switch6.ethg[2] <--> C2 <--> switch7.ethg[0];
        switch6.ethg[3] <--> C2 <--> switch8.ethg[0];

        switch7.ethg[1] <--> C2 <--> ES2.ethg;

        switch8.ethg[1] <--> C2 <--> switch9.ethg[0];

        switch9.ethg[1] <--> C2 <--> switch10.ethg[1];

        switch10.ethg[0] <--> C2 <--> rsu[3].ethg;
        switch10.ethg[2] <--> C2 <--> switch11.ethg[0];
        switch10.ethg[3] <--> C2 <--> switch12.ethg[0];
        switch10.ethg[4] <--> C2 <--> switch17.ethg[0];
        //switch10.ethg[4] <--> C2 <--> switch15.ethg[0];

        switch11.ethg[1] <--> C2 <--> ES3.ethg;

        switch12.ethg[1] <--> C2 <--> switch13.ethg[0];

        switch13.ethg[1] <--> C2 <--> ES4.ethg;
        switch13.ethg[2] <--> C2 <--> switch14.ethg[0];

        switch14.ethg[1] <--> C2 <--> ES5.ethg;

        switch15.ethg[1] <--> C2 <--> switch16.ethg[0];
        switch15.ethg[2] <--> C2 <--> ES7.ethg;
        switch15.ethg[3] <--> C2 <--> rsu[4].ethg;

        switch16.ethg[1] <--> C2 <--> ES6.ethg;

        switch17.ethg[1] <--> C2 <--> switch18.ethg[0];
//
        switch18.ethg[1] <--> C2 <--> switch15.ethg[0];
//
}

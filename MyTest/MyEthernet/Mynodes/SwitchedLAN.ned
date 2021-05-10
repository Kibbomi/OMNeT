//
// Copyright (C) 2003 CTIE, Monash University
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//



package Mynodes;

import inet.common.misc.ThruputMeteringChannel;
import inet.linklayer.ethernet.EtherBus;
import inet.linklayer.ethernet.EtherHub;
import inet.node.ethernet.EtherHost;
import inet.node.ethernet.EtherSwitch;
import ned.DatarateChannel;


network SwitchedLAN
{
    types:
        channel C extends DatarateChannel
        {
            delay = 0.1us;
            datarate = 100Mbps;
        }
    submodules:
        hostA: EtherHost {
            parameters:
                @display("p=250,100");
        }
        hostB: EtherHost {
            parameters:
                @display("p=400,200");
        }
        hostC: EtherHost {
            parameters:
                @display("p=250,300");
        }
        hostD: EtherHost {
            parameters:
                @display("p=100,200");
        }
        switch: EtherSwitch {
            parameters:
                @display("p=250,200");
            gates:
                ethg[4];
        }
    connections:
        switch.ethg[0] <--> C <--> hostA.ethg;
        switch.ethg[1] <--> C <--> hostB.ethg;
        switch.ethg[2] <--> C <--> hostC.ethg;
        switch.ethg[3] <--> C <--> hostD.ethg;
}

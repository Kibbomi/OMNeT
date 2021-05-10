//
// Copyright (C) 2008 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
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

package Mynodes;

//802.11p
import org.car2x.veins.base.modules.*;
import org.car2x.veins.modules.nic.Nic80211p;


//Ethernet
import inet.linklayer.contract.IEthernetInterface;
import inet.networklayer.common.InterfaceTable;

module MyRSU_EN
{
    parameters:
        //802.11p
        string applType; //type of the application layer
        string nicType = default("Nic80211p"); // type of network interface card

        //Ethernet
        bool csmacdSupport = default(true);  // by default use CSMA/CD
        string fcsMode @enum("declared","computed") = default("declared");
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        *.fcsMode = fcsMode;
        eth.csmacdSupport = csmacdSupport;
        @networkNode();
        @labels(node,ethernet-node);
        @display("i=device/pc2");

    gates:
        //802.11p
        input veinsradioIn; // gate for sendDirect

        //Ethernet
        inout ethg @labels(EtherFrame-conn);

    submodules:
        //802.11p
        //appl: <applType> like org.car2x.veins.base.modules.IBaseApplLayer {
         //   parameters:
          //      @display("p=60,50");
        //}

        appl: <applType> like org.car2x.veins.base.modules.IMyBaseApplLayer {
            parameters:
                @display("p=133,54");
        }
        nic: <nicType> like org.car2x.veins.modules.nic.INic80211p {
            parameters:
                @display("p=60,166");
        }

        mobility: BaseMobility {
            parameters:
                @display("p=130,172;i=block/cogwheel");
        }

        //Ethernet
        //app: EtherTrafGen {
        //    @display("p=200,100");
        //}
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=125,240;is=s");
        }
        eth: <default("EthernetInterface")> like IEthernetInterface {
            parameters:
                @display("p=200,239,row,150;q=txQueue");
        }

    connections:
        //Ethernet
        eth.upperLayerOut --> appl.ethIn;
        eth.upperLayerIn <-- appl.ethOut;
       
        eth.phys <--> { @display("m=s"); } <--> ethg;
        
        //802.11p
        nic.upperLayerOut --> appl.lowerLayerIn;
        nic.upperLayerIn <-- appl.lowerLayerOut;
        nic.upperControlOut --> appl.lowerControlIn;
        nic.upperControlIn <-- appl.lowerControlOut;

        veinsradioIn --> nic.radioIn;
}

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

package flexi_obsmodules.src.Networks.Medium;

import inet.node.ethernet.EtherHost2;
import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;


//
// TODO Auto-generated network
//
network Medium
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=309,27");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=49,134");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=239,140");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=572,127");
        }
        flexi_OBS_SuperNode4: Flexi_OBS_SuperNode {
            @display("p=197,295");
        }
        flexi_OBS_SuperNode5: Flexi_OBS_SuperNode {
            @display("p=404,308");
        }
        flexi_OBS_SuperNode6: Flexi_OBS_SuperNode {
            @display("p=643,286");
        }
        flexi_OBS_SuperNode7: Flexi_OBS_SuperNode {
            @display("p=38,476");
        }
        flexi_OBS_SuperNode8: Flexi_OBS_SuperNode {
            @display("p=425,493");
        }
        flexi_OBS_SuperNode9: Flexi_OBS_SuperNode {
            @display("p=637,487");
        }
        flexi_OBS_SuperNode10: Flexi_OBS_SuperNode {
            @display("p=404,660");
        }
        fibre: Fibre {
            fibreLength = 18km;
            @display("p=140,140");
        }
        fibre1: Fibre {
            fibreLength = 15km;
            @display("p=373,134");
        }
        fibre2: Fibre {
            fibreLength = 14km;
            @display("p=38,247");
        }
        fibre3: Fibre {
            fibreLength = 15km;
            @display("p=309,301");
        }
        fibre4: Fibre {
            fibreLength = 12km;
            @display("p=503,308");
        }
        fibre5: Fibre {
            fibreLength = 15km;
            @display("p=537,487");
        }
        fibre6: Fibre {
            fibreLength = 18km;
            @display("p=239,487");
        }
        fibre7: Fibre {
            fibreLength = 18km;
            @display("p=556,584");
        }
        fibre8: Fibre {
            fibreLength = 9km;
            @display("p=412,570");
        }
        fibre9: Fibre {
            fibreLength = 27km;
            @display("p=179,577");
        }
        fibre10: Fibre {
            fibreLength = 20km;
            @display("p=113,49");
        }
        fibre11: Fibre {
            fibreLength = 14km;
            @display("p=262,78");
        }
        fibre12: Fibre {
            fibreLength = 14km;
            @display("p=562,55");
        }
        fibre13: Fibre {
            fibreLength = 11km;
            @display("p=128,247");
        }
        fibre14: Fibre {
            fibreLength = 9km;
            @display("p=140,360");
        }
        fibre15: Fibre {
            fibreLength = 14km;
            @display("p=218,219");
        }
        fibre16: Fibre {
            fibreLength = 35km;
            @display("p=262,360");
        }
        fibre17: Fibre {
            fibreLength = 10km;
            @display("p=595,202");
        }
        fibre18: Fibre {
            fibreLength = 10km;
            @display("p=318,225");
        }
        fibre19: Fibre {
            fibreLength = 16km;
            @display("p=464,163");
        }
        fibre20: Fibre {
            fibreLength = 20km;
            @display("p=734,196");
        }
        fibre21: Fibre {
            fibreLength = 10km;
            @display("p=404,377");
        }
        fibre22: Fibre {
            fibreLength = 12km;
            @display("p=556,366");
        }
        fibre23: Fibre {
            fibreLength = 12km;
            @display("p=637,377");
        }
        fibre24: Fibre {
            fibreLength = 18km;
            @display("p=218,437");
        }
        fibre25: Fibre {
            fibreLength = 34km;
            @display("p=425,234");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=686,46");
        }
    connections:
        flexi_OBS_SuperNode.links++ <--> fibre10.left;
        flexi_OBS_SuperNode1.links++ <--> fibre10.right;
        flexi_OBS_SuperNode.links++ <--> fibre11.left;
        fibre11.right <--> flexi_OBS_SuperNode2.links++;
        flexi_OBS_SuperNode.links++ <--> fibre12.left;
        fibre12.right <--> flexi_OBS_SuperNode3.links++;
        flexi_OBS_SuperNode10.links++ <--> fibre8.right;
        flexi_OBS_SuperNode10.links++ <--> fibre7.right;
        flexi_OBS_SuperNode10.links++ <--> fibre9.right;
        fibre9.left <--> flexi_OBS_SuperNode7.links++;
        flexi_OBS_SuperNode8.links++ <--> fibre8.left;
        flexi_OBS_SuperNode9.links++ <--> fibre7.left;
        flexi_OBS_SuperNode7.links++ <--> fibre6.left;
        fibre6.right <--> flexi_OBS_SuperNode8.links++;
        flexi_OBS_SuperNode8.links++ <--> fibre5.left;
        fibre5.right <--> flexi_OBS_SuperNode9.links++;
        flexi_OBS_SuperNode1.links++ <--> fibre.left;
        fibre.right <--> flexi_OBS_SuperNode2.links++;
        flexi_OBS_SuperNode2.links++ <--> fibre1.left;
        fibre1.right <--> flexi_OBS_SuperNode3.links++;
        flexi_OBS_SuperNode4.links++ <--> fibre3.left;
        fibre3.right <--> flexi_OBS_SuperNode5.links++;
        flexi_OBS_SuperNode5.links++ <--> fibre4.left;
        fibre4.right <--> flexi_OBS_SuperNode6.links++;
        flexi_OBS_SuperNode1.links++ <--> fibre2.left;
        fibre2.right <--> flexi_OBS_SuperNode7.links++;
        flexi_OBS_SuperNode4.links++ <--> fibre16.left;
        fibre16.right <--> flexi_OBS_SuperNode10.links++;
        flexi_OBS_SuperNode7.links++ <--> fibre14.left;
        fibre14.right <--> flexi_OBS_SuperNode4.links++;
        flexi_OBS_SuperNode1.links++ <--> fibre13.left;
        fibre13.right <--> flexi_OBS_SuperNode4.links++;
        flexi_OBS_SuperNode4.links++ <--> fibre15.right;
        fibre15.left <--> flexi_OBS_SuperNode2.links++;
        flexi_OBS_SuperNode2.links++ <--> fibre18.left;
        fibre18.right <--> flexi_OBS_SuperNode5.links++;
        flexi_OBS_SuperNode3.links++ <--> fibre17.left;
        fibre17.right <--> flexi_OBS_SuperNode6.links++;
        flexi_OBS_SuperNode.links++ <--> fibre19.left;
        fibre19.right <--> flexi_OBS_SuperNode6.links++;
        flexi_OBS_SuperNode3.links++ <--> fibre20.left;
        flexi_OBS_SuperNode9.links++ <--> fibre20.right;
        flexi_OBS_SuperNode5.links++ <--> fibre21.left;
        fibre21.right <--> flexi_OBS_SuperNode8.links++;
        flexi_OBS_SuperNode8.links++ <--> fibre22.right;
        fibre22.left <--> flexi_OBS_SuperNode6.links++;
        flexi_OBS_SuperNode6.links++ <--> fibre23.left;
        fibre23.right <--> flexi_OBS_SuperNode9.links++;
        flexi_OBS_SuperNode7.links++ <--> fibre25.left;
        fibre25.right <--> flexi_OBS_SuperNode3.links++;
        flexi_OBS_SuperNode7.links++ <--> fibre24.left;
        fibre24.right <--> flexi_OBS_SuperNode5.links++;
}

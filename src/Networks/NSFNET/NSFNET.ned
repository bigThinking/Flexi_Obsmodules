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

package flexi_obsmodules.src.Networks.NSFNET;

import inet.common.scenario.ScenarioManager;
import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;
import flexi_obsmodules.src.Networks.BaseNetwork;


network NSFNET extends BaseNetwork
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=114,38");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=25,197");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=64,383");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=161,204");
        }
        fibre: Fibre {
            fibreLength = 11km;
            @display("p=56,118");
        }
        fibre1: Fibre {
            fibreLength = 6km;
            @display("p=40,286");
        }
        fibre2: Fibre {
            fibreLength = 10km;
            @display("p=87,204");
        }
        fibre3: Fibre {
            fibreLength = 16km;
            @display("p=140,138");
        }
        flexi_OBS_SuperNode4: Flexi_OBS_SuperNode {
            @display("p=221,276");
        }
        flexi_OBS_SuperNode5: Flexi_OBS_SuperNode {
            @display("p=221,422");
        }
        flexi_OBS_SuperNode6: Flexi_OBS_SuperNode {
            @display("p=360,236");
        }
        fibre4: Fibre {
            fibreLength = 20km;
            @display("p=140,398");
        }
        fibre5: Fibre {
            fibreLength = 11km;
            @display("p=221,344");
        }
        fibre6: Fibre {
            fibreLength = 6km;
            @display("p=153,286");
        }
        fibre7: Fibre {
            fibreLength = 16km;
            @display("p=294,249");
        }
        flexi_OBS_SuperNode7: Flexi_OBS_SuperNode {
            @display("p=466,118");
        }
        flexi_OBS_SuperNode8: Flexi_OBS_SuperNode {
            @display("p=595,158");
        }
        flexi_OBS_SuperNode9: Flexi_OBS_SuperNode {
            @display("p=578,416");
        }
        fibre8: Fibre {
            fibreLength = 11km;
            @display("p=585,257");
        }
        fibre9: Fibre {
            fibreLength = 7km;
            @display("p=409,204");
        }
        fibre10: Fibre {
            fibreLength = 7km;
            @display("p=514,197");
        }
        fibre11: Fibre {
            fibreLength = 12km;
            @display("p=384,422");
        }
        flexi_OBS_SuperNode10: Flexi_OBS_SuperNode {
            @display("p=578,24;b=18,8");
        }
        flexi_OBS_SuperNode11: Flexi_OBS_SuperNode {
            @display("p=748,24");
        }
        flexi_OBS_SuperNode12: Flexi_OBS_SuperNode {
            @display("p=756,359");
        }
        flexi_OBS_SuperNode13: Flexi_OBS_SuperNode {
            @display("p=795,171");
        }
        fibre12: Fibre {
            fibreLength = 8km;
            @display("p=660,24");
        }
        fibre14: Fibre {
            fibreLength = 8km;
            @display("p=795,85");
        }
        fibre15: Fibre {
            fibreLength = 3km;
            @display("p=819,286");
        }
        fibre16: Fibre {
            fibreLength = 24km;
            @display("p=279,107;is=s");
        }
        fibre17: Fibre {
            fibreLength = 5km;
            @display("p=679,85");
        }
        fibre18: Fibre {
            fibreLength = 3km;
            @display("p=744,276");
        }
        fibre19: Fibre {
            fibreLength = 20km;
            @display("p=466,377");
        }
        fibre20: Fibre {
            fibreLength = 5km;
            @display("p=660,225");
        }
        fibre21: Fibre {
            fibreLength = 18km;
            @display("p=353,107;is=s");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=899,24");
        }
        scenarioManager: ScenarioManager {
            @display("p=876,106");
        }
    connections:
        flexi_OBS_SuperNode.links++ <--> fibre.left;
        flexi_OBS_SuperNode1.links++ <--> fibre.right;
        flexi_OBS_SuperNode1.links++ <--> fibre1.left;
        flexi_OBS_SuperNode2.links++ <--> fibre1.right;
        flexi_OBS_SuperNode.links++ <--> fibre3.left;
        flexi_OBS_SuperNode2.links++ <--> fibre3.right;
        flexi_OBS_SuperNode3.links++ <--> fibre2.right;
        flexi_OBS_SuperNode1.links++ <--> fibre2.left;
        flexi_OBS_SuperNode2.links++ <--> fibre4.left;
        flexi_OBS_SuperNode5.links++ <--> fibre4.right;
        flexi_OBS_SuperNode3.links++ <--> fibre6.left;
        flexi_OBS_SuperNode4.links++ <--> fibre6.right;
        flexi_OBS_SuperNode4.links++ <--> fibre5.left;
        flexi_OBS_SuperNode5.links++ <--> fibre5.right;
        flexi_OBS_SuperNode4.links++ <--> fibre7.left;
        flexi_OBS_SuperNode6.links++ <--> fibre7.right;
        flexi_OBS_SuperNode6.links++ <--> fibre9.left;
        flexi_OBS_SuperNode7.links++ <--> fibre9.right;
        flexi_OBS_SuperNode7.links++ <--> fibre10.left;
        flexi_OBS_SuperNode8.links++ <--> fibre10.right;
        flexi_OBS_SuperNode9.links++ <--> fibre8.right;
        flexi_OBS_SuperNode8.links++ <--> fibre8.left;
        flexi_OBS_SuperNode5.links++ <--> fibre11.left;
        flexi_OBS_SuperNode9.links++ <--> fibre11.right;
        flexi_OBS_SuperNode3.links++ <--> fibre16.left;
        flexi_OBS_SuperNode10.links++ <--> fibre16.right;
        flexi_OBS_SuperNode10.links++ <--> fibre12.left;
        flexi_OBS_SuperNode11.links++ <--> fibre12.right;
        flexi_OBS_SuperNode11.links++ <--> fibre17.right;
        flexi_OBS_SuperNode8.links++ <--> fibre17.left;
        flexi_OBS_SuperNode11.links++ <--> fibre18.left;
        flexi_OBS_SuperNode12.links++ <--> fibre18.right;
        flexi_OBS_SuperNode5.links++ <--> fibre19.left;
        flexi_OBS_SuperNode12.links++ <--> fibre19.right;
        flexi_OBS_SuperNode13.links++ <--> fibre15.right;
        flexi_OBS_SuperNode12.links++ <--> fibre15.left;
        flexi_OBS_SuperNode13.links++ <--> fibre14.right;
        flexi_OBS_SuperNode10.links++ <--> fibre14.left;
        flexi_OBS_SuperNode8.links++ <--> fibre20.left;
        flexi_OBS_SuperNode13.links++ <--> fibre20.right;
        flexi_OBS_SuperNode.links++ <--> fibre21.left;
        flexi_OBS_SuperNode7.links++ <--> fibre21.right;
}

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

package flexi_obsmodules.src.Networks.SIMPLE;

import inet.common.scenario.ScenarioManager;
import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;
import flexi_obsmodules.src.Networks.BaseNetwork;

//
// TODO Auto-generated network
//
network SIMPLE extends BaseNetwork
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=412,91");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=201,83");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=53,187");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=201,318");
        }
        flexi_OBS_SuperNode4: Flexi_OBS_SuperNode {
            @display("p=398,318");
        }
        flexi_OBS_SuperNode5: Flexi_OBS_SuperNode {
            @display("p=590,204");
        }
        fibre: Fibre {
            fibreLength = 11km;
            @display("p=315,83");
        }
        fibre1: Fibre {
            fibreLength = 16km;
            @display("p=119,130");
        }
        fibre2: Fibre {
            fibreLength = 22km;
            @display("p=125,261");
        }
        fibre3: Fibre {
            fibreLength = 18km;
            @display("p=299,318");
        }
        fibre4: Fibre {
            fibreLength = 15km;
            @display("p=487,268");
        }
        fibre5: Fibre {
            fibreLength = 17km;
            @display("p=502,150");
        }
        fibre6: Fibre {
            fibreLength = 19km;
            @display("p=324,214");
        }
        fibre7: Fibre {
            fibreLength = 20km;
            @display("p=266,214");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=573,31");
        }
        scenarioManager: ScenarioManager {
            @display("p=569,83");
        }
    connections:
        flexi_OBS_SuperNode.links++ <--> fibre.left;
        flexi_OBS_SuperNode1.links++ <--> fibre.right;
        flexi_OBS_SuperNode1.links++ <--> fibre1.left;
        flexi_OBS_SuperNode2.links++ <--> fibre1.right;
        flexi_OBS_SuperNode2.links++ <--> fibre2.left;
        flexi_OBS_SuperNode3.links++ <--> fibre2.right;
        flexi_OBS_SuperNode3.links++ <--> fibre3.left;
        flexi_OBS_SuperNode4.links++ <--> fibre3.right;
        flexi_OBS_SuperNode4.links++ <--> fibre4.left;
        flexi_OBS_SuperNode5.links++ <--> fibre4.right;
        flexi_OBS_SuperNode5.links++ <--> fibre5.left;
        flexi_OBS_SuperNode.links++ <--> fibre5.right;
        flexi_OBS_SuperNode.links++ <--> fibre6.right;
        fibre6.left <--> flexi_OBS_SuperNode3.links++;
        flexi_OBS_SuperNode1.links++ <--> fibre7.right;
        fibre7.left <--> flexi_OBS_SuperNode4.links++;
}

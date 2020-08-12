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

package flexi_obsmodules.src.Networks.TestNetwork5;

import flexi_obsmodules.src.Base.CoreNode.Flexi_OBS_CoreNode;
import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;
import flexi_obsmodules.src.Networks.BaseNetwork;

//
// TODO Auto-generated network
//
network TestNetwork5 extends BaseNetwork
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=68,212");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=510,203");
        }
        fibre: Fibre {
            @display("p=107,96");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=280,34");
        }
        flexi_OBS_CoreNode: Flexi_OBS_CoreNode {
            @display("p=227,212");
        }
        flexi_OBS_CoreNode1: Flexi_OBS_CoreNode {
            @display("p=353,212");
        }
        fibre1: Fibre {
            @display("p=266,103");
        }
        fibre2: Fibre {
            @display("p=430,83");
        }
    connections:
        flexi_OBS_SuperNode.links++ <--> fibre.left;
        fibre.right <--> flexi_OBS_CoreNode.inOut++;
        flexi_OBS_CoreNode.inOut++ <--> fibre1.left;
        flexi_OBS_CoreNode1.inOut++ <--> fibre1.right;
        flexi_OBS_CoreNode1.inOut++ <--> fibre2.left;
        flexi_OBS_SuperNode1.links++ <--> fibre2.right;
}


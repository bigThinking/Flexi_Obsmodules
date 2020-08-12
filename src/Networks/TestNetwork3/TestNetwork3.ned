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

package flexi_obsmodules.src.Networks.TestNetwork3;

import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;


//
// TODO Auto-generated network
//
network TestNetwork3
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=183,170");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=183,38");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=325,284");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=67,284");
        }
        fibre: Fibre {
            @display("p=265,216");
        }
        fibre1: Fibre {
            @display("p=97,223");
        }
        fibre2: Fibre {
            @display("p=183,111");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=314,58");
        }
    connections:
        fibre2.left <--> flexi_OBS_SuperNode1.links++;
        fibre2.right <--> flexi_OBS_SuperNode.links++;
        flexi_OBS_SuperNode.links++ <--> fibre1.left;
        flexi_OBS_SuperNode.links++ <--> fibre.left;
        fibre1.right <--> flexi_OBS_SuperNode3.links++;
        fibre.right <--> flexi_OBS_SuperNode2.links++;
}

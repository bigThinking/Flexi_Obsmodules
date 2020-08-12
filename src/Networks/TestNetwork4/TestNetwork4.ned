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

package flexi_obsmodules.src.Networks.TestNetwork4;

import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;
import flexi_obsmodules.src.Networks.BaseNetwork;

//
// TODO Auto-generated network
//
network TestNetwork4 extends BaseNetwork
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=83,98");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=225,98");
        }
        fibre: Fibre {
            @display("p=156,42");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=280,34");
        }
    connections:
        flexi_OBS_SuperNode.links++ <--> fibre.left;
        flexi_OBS_SuperNode1.links++ <--> fibre.right;
}

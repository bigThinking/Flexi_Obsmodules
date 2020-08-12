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

package flexi_obsmodules.src.Networks.Star;

import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;


network Star
{
    submodules:
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=448,18");
        }
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=261,202");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=471,193");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=261,39");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=39,193");
        }
        flexi_OBS_SuperNode4: Flexi_OBS_SuperNode {
            @display("p=432,346");
        }
        flexi_OBS_SuperNode5: Flexi_OBS_SuperNode {
            @display("p=125,356;is=l");
        }
        fibre: Fibre {
            @display("p=385,278");
        }
        fibre1: Fibre {
            @display("p=261,307");
        }
        fibre2: Fibre {
            @display("p=362,193");
        }
        fibre3: Fibre {
            @display("p=255,134");
        }
        fibre4: Fibre {
            @display("p=157,202");
        }
    connections:
        flexi_OBS_SuperNode3.links++ <--> fibre4.left;
        fibre4.right <--> flexi_OBS_SuperNode.links++;
        flexi_OBS_SuperNode.links++ <--> fibre2.left;
        fibre2.right <--> flexi_OBS_SuperNode1.links++;
        flexi_OBS_SuperNode.links++ <--> fibre1.left;
        fibre1.right <--> flexi_OBS_SuperNode5.links++;
        fibre3.right <--> flexi_OBS_SuperNode2.links++;
        fibre3.left <--> flexi_OBS_SuperNode.links++;
        fibre.right <--> flexi_OBS_SuperNode4.links++;
        flexi_OBS_SuperNode.links++ <--> fibre.left;
}

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

package flexi_obsmodules.src.Networks.Ring;

import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;


network Ring
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=63,59");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=258,110");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=94,224");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=219,322");
        }
        flexi_OBS_SuperNode4: Flexi_OBS_SuperNode {
            @display("p=358,249");
        }
        flexi_OBS_SuperNode5: Flexi_OBS_SuperNode {
            @display("p=424,128");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=378,40");
        }
        fibre: Fibre {
            @display("p=139,288");
        }
        fibre1: Fibre {
            @display("p=308,306");
        }
        fibre2: Fibre {
            @display("p=399,185");
        }
        fibre3: Fibre {
            @display("p=338,111");
        }
        fibre4: Fibre {
            @display("p=178,40");
        }
        fibre5: Fibre {
            @display("p=44,149");
        }
    connections:
        flexi_OBS_SuperNode.links++ <--> fibre5.left;
        fibre5.right <--> flexi_OBS_SuperNode2.links++;
        flexi_OBS_SuperNode2.links++ <--> fibre.left;
        fibre.right <--> flexi_OBS_SuperNode3.links++;
        flexi_OBS_SuperNode3.links++ <--> fibre1.left;
        fibre1.right <--> flexi_OBS_SuperNode4.links++;
        flexi_OBS_SuperNode4.links++ <--> fibre2.left;
        fibre2.right <--> flexi_OBS_SuperNode5.links++;
        flexi_OBS_SuperNode5.links++ <--> fibre3.left;
        fibre3.right <--> flexi_OBS_SuperNode1.links++;
        flexi_OBS_SuperNode1.links++ <--> fibre4.left;
        fibre4.right <--> flexi_OBS_SuperNode.links++;
}

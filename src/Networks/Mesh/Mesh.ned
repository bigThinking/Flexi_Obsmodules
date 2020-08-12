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

package flexi_obsmodules.src.Networks.Mesh;

import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;


network Mesh
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=153,85");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=366,97");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=114,254");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=484,328");
        }
        flexi_OBS_SuperNode4: Flexi_OBS_SuperNode {
            @display("p=285,199");
        }
        flexi_OBS_SuperNode5: Flexi_OBS_SuperNode {
            @display("p=477,190");
        }
        flexi_OBS_SuperNode6: Flexi_OBS_SuperNode {
            @display("p=255,328");
        }
        fibre: Fibre {
            @display("p=232,80");
        }
        fibre1: Fibre {
            @display("p=107,177");
        }
        fibre2: Fibre {
            @display("p=446,134");
        }
        fibre3: Fibre {
            @display("p=487,271");
        }
        fibre4: Fibre {
            @display("p=386,346");
        }
        fibre5: Fibre {
            @display("p=159,327");
        }
        fibre6: Fibre {
            @display("p=179,154");
        }
        fibre7: Fibre {
            @display("p=414,288");
        }
        fibre8: Fibre {
            @display("p=366,160");
        }
        fibre9: Fibre {
            @display("p=212,277");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=497,49");
        }
    connections:
        flexi_OBS_SuperNode.links++ <--> fibre1.left;
        flexi_OBS_SuperNode.links++ <--> fibre6.left;
        flexi_OBS_SuperNode.links++ <--> fibre.left;
        fibre1.right <--> flexi_OBS_SuperNode2.links++;
        flexi_OBS_SuperNode2.links++ <--> fibre5.left;
        flexi_OBS_SuperNode2.links++ <--> fibre9.left;
        fibre5.right <--> flexi_OBS_SuperNode6.links++;
        flexi_OBS_SuperNode4.links++ <--> fibre9.right;
        fibre6.right <--> flexi_OBS_SuperNode4.links++;
        fibre.right <--> flexi_OBS_SuperNode1.links++;
        fibre4.right <--> flexi_OBS_SuperNode3.links++;
        fibre7.right <--> flexi_OBS_SuperNode3.links++;
        fibre3.right <--> flexi_OBS_SuperNode3.links++;
        fibre3.left <--> flexi_OBS_SuperNode5.links++;
        fibre4.left <--> flexi_OBS_SuperNode6.links++;
        flexi_OBS_SuperNode1.links++ <--> fibre2.left;
        fibre2.right <--> flexi_OBS_SuperNode5.links++;
        flexi_OBS_SuperNode4.links++ <--> fibre7.left;
        flexi_OBS_SuperNode4.links++ <--> fibre8.left;
        fibre8.right <--> flexi_OBS_SuperNode1.links++;
}

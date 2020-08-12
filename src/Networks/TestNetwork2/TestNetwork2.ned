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

package flexi_obsmodules.src.Networks.TestNetwork2;

import flexi_obsmodules.src.Base.CoreNode.Flexi_OBS_CoreNode;
import flexi_obsmodules.src.Base.EdgeNode.Flexi_OBS_EdgeNode;
import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;
import flexi_obsmodules.src.Networks.BaseNetwork;


//
// TODO Auto-generated network
//
network TestNetwork2 extends BaseNetwork
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=174,118");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=735,143");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=264,292");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=40,292");
        }
        flexi_OBS_SuperNode4: Flexi_OBS_SuperNode {
            @display("p=639,292");
        }
        flexi_OBS_SuperNode5: Flexi_OBS_SuperNode {
            @display("p=837,310");
        }
        fibre1: Fibre {
            fibreLength = 1km;
            @display("p=587,104");
        }
        fibre2: Fibre {
            @display("p=747,311");
        }
        fibre3: Fibre {
            @display("p=815,213");
        }
        fibre4: Fibre {
            @display("p=641,208");
        }
        fibre5: Fibre {
            @display("p=143,299");
        }
        fibre6: Fibre {
            @display("p=233,203");
        }
        fibre7: Fibre {
            @display("p=79,198");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=804,34");
        }
        fibre: Fibre {
            @display("p=431,220");
        }
        flexi_OBS_CoreNode: Flexi_OBS_CoreNode {
            @display("p=408,91");
        }
        fibre8: Fibre {
            fibreLength = 1km;
            @display("p=269,85");
        }
    connections:
        fibre4.right <--> flexi_OBS_SuperNode4.links++;
        flexi_OBS_SuperNode4.links++ <--> fibre2.left;
        fibre2.right <--> flexi_OBS_SuperNode5.links++;
        fibre3.right <--> flexi_OBS_SuperNode5.links++;
        flexi_OBS_SuperNode.links++ <--> fibre7.left;
        fibre5.right <--> flexi_OBS_SuperNode2.links++;
        flexi_OBS_SuperNode2.links++ <--> fibre6.right;
        fibre6.left <--> flexi_OBS_SuperNode.links++;
        flexi_OBS_SuperNode.links++ <--> fibre.left;
        flexi_OBS_SuperNode1.links++ <--> fibre4.left;
        flexi_OBS_SuperNode1.links++ <--> fibre3.left;
        fibre7.right <--> flexi_OBS_SuperNode3.links++;
        flexi_OBS_SuperNode3.links++ <--> fibre5.left;
        fibre1.right <--> flexi_OBS_SuperNode1.links++;
        fibre.right <--> flexi_OBS_SuperNode1.links++;
        fibre1.left <--> flexi_OBS_CoreNode.inOut++;
        flexi_OBS_CoreNode.inOut++ <--> fibre8.right;
        flexi_OBS_SuperNode.links++ <--> fibre8.left;
}

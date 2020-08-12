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

package flexi_obsmodules.src.Networks.Fish;

import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;


//
// TODO Auto-generated network
//
network Fish
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=54,39");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=54,147");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=54,257");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=234,147");
        }
        flexi_OBS_SuperNode4: Flexi_OBS_SuperNode {
            @display("p=364,61");
        }
        flexi_OBS_SuperNode5: Flexi_OBS_SuperNode {
            @display("p=314,237");
        }
        flexi_OBS_SuperNode6: Flexi_OBS_SuperNode {
            @display("p=492,237");
        }
        flexi_OBS_SuperNode7: Flexi_OBS_SuperNode {
            @display("p=545,128");
        }
        fibre: Fibre {
            @display("p=148,61");
        }
        fibre1: Fibre {
            @display("p=137,244");
        }
        fibre2: Fibre {
            @display("p=132,140");
        }
        fibre3: Fibre {
            @display("p=284,85");
        }
        fibre4: Fibre {
            @display("p=463,79");
        }
        fibre5: Fibre {
            @display("p=550,198");
        }
        fibre6: Fibre {
            @display("p=392,248");
        }
        fibre7: Fibre {
            @display("p=258,195");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=540,18");
        }
    connections:
        flexi_OBS_SuperNode.links++ <--> fibre.left;
        fibre.right <--> flexi_OBS_SuperNode3.links++;
        flexi_OBS_SuperNode1.links++ <--> fibre2.left;
        flexi_OBS_SuperNode3.links++ <--> fibre2.right;
        flexi_OBS_SuperNode2.links++ <--> fibre1.left;
        flexi_OBS_SuperNode3.links++ <--> fibre1.right;
        flexi_OBS_SuperNode3.links++ <--> fibre3.left;
        flexi_OBS_SuperNode3.links++ <--> fibre7.left;
        fibre3.right <--> flexi_OBS_SuperNode4.links++;
        flexi_OBS_SuperNode5.links++ <--> fibre7.right;
        flexi_OBS_SuperNode5.links++ <--> fibre6.left;
        fibre6.right <--> flexi_OBS_SuperNode6.links++;
        flexi_OBS_SuperNode4.links++ <--> fibre4.left;
        fibre4.right <--> flexi_OBS_SuperNode7.links++;
        flexi_OBS_SuperNode6.links++ <--> fibre5.left;
        flexi_OBS_SuperNode7.links++ <--> fibre5.right;
}

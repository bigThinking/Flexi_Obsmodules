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

package flexi_obsmodules.src.Networks.TestNetwork;

import inet.applications.generic.IpvxTrafGen;
import flexi_obsmodules.src.Base.CoreNode.Flexi_OBS_CoreNode;
import flexi_obsmodules.src.Base.EdgeNode.Flexi_OBS_EdgeNode;
import flexi_obsmodules.src.Base.Fibre.Fibre;
import flexi_obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import flexi_obsmodules.src.Networks.BaseNetwork;

//
// TODO Auto-generated network
//
network TestNetwork extends BaseNetwork
{
    submodules:
        flexi_OBS_EdgeNode: Flexi_OBS_EdgeNode {
            @display("p=167,43");
        }
        flexi_OBS_EdgeNode1: Flexi_OBS_EdgeNode {
            @display("p=528,384");
        }
        flexi_OBS_CoreNode: Flexi_OBS_CoreNode {
            @display("p=319,236");
        }
        flexi_OBS_CoreNode1: Flexi_OBS_CoreNode {
            @display("p=367,89");
        }
        flexi_OBS_CoreNode2: Flexi_OBS_CoreNode {
            @display("p=528,205");
        }
        flexi_OBS_CoreNode3: Flexi_OBS_CoreNode {
            @display("p=91,146");
        }
        flexi_OBS_CoreNode4: Flexi_OBS_CoreNode {
            @display("p=91,303");
        }
        flexi_OBS_CoreNode5: Flexi_OBS_CoreNode {
            @display("p=271,390");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=481,30");
        }
        fibre: Fibre {
            @display("p=265,50");
        }
        fibre1: Fibre {
            @display("p=46,61");
        }
        fibre2: Fibre {
            @display("p=96,215");
        }
        fibre3: Fibre {
            @display("p=222,141");
        }
        fibre4: Fibre {
            @display("p=423,330");
        }
        fibre5: Fibre {
            @display("p=138,366");
        }
        fibre6: Fibre {
            @display("p=542,297");
        }
        fibre7: Fibre {
            @display("p=374,401");
        }
        fibre8: Fibre {
            @display("p=479,139");
        }
    connections:

        flexi_OBS_EdgeNode.obsInOut++ <--> fibre1.left;
        flexi_OBS_EdgeNode.obsInOut++ <--> fibre.left;
        flexi_OBS_EdgeNode.obsInOut++ <--> fibre3.left;
        flexi_OBS_EdgeNode1.obsInOut++ <--> fibre6.right;
        flexi_OBS_EdgeNode1.obsInOut++ <--> fibre4.right;
        flexi_OBS_EdgeNode1.obsInOut++ <--> fibre7.right;

        fibre1.right <--> flexi_OBS_CoreNode3.inOut++;
        fibre3.right <--> flexi_OBS_CoreNode.inOut++;
        fibre.right <--> flexi_OBS_CoreNode1.inOut++;
       
        fibre4.left <--> flexi_OBS_CoreNode.inOut++;
        fibre6.left <--> flexi_OBS_CoreNode2.inOut++;
        fibre7.left <--> flexi_OBS_CoreNode5.inOut++;

        fibre8.left <--> flexi_OBS_CoreNode1.inOut++;
        fibre8.right <--> flexi_OBS_CoreNode2.inOut++;

        fibre5.left <--> flexi_OBS_CoreNode5.inOut++;
        fibre5.right <--> flexi_OBS_CoreNode4.inOut++;
       
        fibre2.left <--> flexi_OBS_CoreNode3.inOut++;
        fibre2.right <--> flexi_OBS_CoreNode4.inOut++;

}

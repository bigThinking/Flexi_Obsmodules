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

package flexi_obsmodules.src.Base.EdgeNode;

//
// TODO auto-generated module
//
simple Flexi_OBS_EdgeRoutingTable like IEdgeRoutingTable
{
    parameters:
        @display("i=block/table2");
        bool inSuperNode;        
        bool recordTableEntries = default(false);
    gates:
        input ackIn @directIn;
}

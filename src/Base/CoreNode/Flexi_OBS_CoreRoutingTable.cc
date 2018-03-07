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

#include "Flexi_OBS_CoreRoutingTable.h"

Define_Module(Flexi_OBS_CoreRoutingTable);

void Flexi_OBS_CoreRoutingTable::initialize()
{
    take(&(this->tableEntries));
}

void Flexi_OBS_CoreRoutingTable::addEntry(NodeRoutingTableEntry *entry)
{

}

cArray* Flexi_OBS_CoreRoutingTable::getEntries()
{
    return &tableEntries;
}

cQueue* Flexi_OBS_CoreRoutingTable::getDestEntries(int value, bool byDest)
{
    if(byDest){
        for(int i=0; i < tableEntries.size(); i++)
        {
            cQueue *q = dynamic_cast<cQueue*>(tableEntries[i]);
            NodeRoutingTableEntry *temp = check_and_cast<NodeRoutingTableEntry *>(q->front());
            if(temp->getDestination() == value)
                return q;
        }
    }else {
        cQueue *q = dynamic_cast<cQueue*>(tableEntries[value]);
        return q;
    }

    return NULL;
}

void Flexi_OBS_CoreRoutingTable::handleMessage(cMessage *msg)
{

}

NodeRoutingTableEntry* Flexi_OBS_CoreRoutingTable::getEntry(int entryId)
{
    return entryIdIndex[entryId];
}

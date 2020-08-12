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

#include "Flexi_OBS_EdgeRoutingTable.h"

Define_Module(Flexi_OBS_EdgeRoutingTable);

void Flexi_OBS_EdgeRoutingTable::initialize()
{
    take(&(this->tableEntries));
    inSuperNode = par("inSuperNode");
    recordTableEntries = par("recordTableEntries");
    shortestPathTable = getShortestPathTable();

    if(recordTableEntries){
        file = new std::ofstream();
        file->open(getFullPath());
    }
}

bool Flexi_OBS_EdgeRoutingTable::addEntry(NodeRoutingTableEntry *entry)
{

}

cArray* Flexi_OBS_EdgeRoutingTable::getEntries()
{
    return &tableEntries;
}

cQueue* Flexi_OBS_EdgeRoutingTable::getDestEntries(int value, bool byDest)
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

int Flexi_OBS_EdgeRoutingTable::entryComparator(cObject *obj1, cObject *obj2)
{
    NodeRoutingTableEntry *o1 = check_and_cast<NodeRoutingTableEntry *>(obj1);
    NodeRoutingTableEntry *o2 = check_and_cast<NodeRoutingTableEntry *>(obj2);

    return (o1->getPheromoneConc() > o2->getPheromoneConc()) ? 1 : (o1->getPheromoneConc() == o2->getPheromoneConc() ? 0 : -1);
}

void Flexi_OBS_EdgeRoutingTable::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{

}

void Flexi_OBS_EdgeRoutingTable::handleMessage(cMessage *msg)
{

}

NodeRoutingTableEntry* Flexi_OBS_EdgeRoutingTable::getEntry(int entryId)
{
    return entryIdIndex[entryId];
}

void Flexi_OBS_EdgeRoutingTable::finish()
{
    if(recordTableEntries){
        if(file->is_open())
            file->close();
    }
}

K_ShortestPathTable* Flexi_OBS_EdgeRoutingTable::getShortestPathTable()
{
    return check_and_cast<K_ShortestPathTable *>(this->getParentModule()->getParentModule()->getSubmodule("k_ShortestPathTable"));
}

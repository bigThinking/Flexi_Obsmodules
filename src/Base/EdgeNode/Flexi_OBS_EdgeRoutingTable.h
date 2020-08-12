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

#ifndef __OBSMODULES_FLEXI_OBS_EDGEROUTINGTABLE_H_
#define __OBSMODULES_FLEXI_OBS_EDGEROUTINGTABLE_H_

#include <omnetpp.h>
#include "NodeRoutingTableEntry_m.h"
#include "EndToEndAck_m.h"
#include <fstream>
#include <iostream>
#include "K_ShortestPathTableEntry_m.h"
#include "K_ShortestPathTable.h"

using namespace omnetpp;
using namespace std;
class NodeRoutingTableEntry;

/**
 * TODO - Generated class
 */
class Flexi_OBS_EdgeRoutingTable : public cSimpleModule, public cListener
{
  public:
    virtual cQueue* getDestEntries(int value, bool byDest=1);
    virtual bool addEntry(NodeRoutingTableEntry *entry);
    void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details);
    virtual NodeRoutingTableEntry* getEntry(int entryId);
    virtual void doRecordTableEntries(char* info){};
  protected:
    int entryCounter = 0;
    bool inSuperNode, recordTableEntries;
    std::ofstream* file;
    cArray tableEntries;
    K_ShortestPathTable* shortestPathTable;
    map<int, NodeRoutingTableEntry*> entryIdIndex;
    virtual void initialize();
    virtual cArray* getEntries();
    static int entryComparator(cObject *obj1, cObject *obj2);
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    K_ShortestPathTable* getShortestPathTable();
};

#endif

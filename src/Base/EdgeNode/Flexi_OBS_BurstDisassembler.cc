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

#include "Flexi_OBS_BurstDisassembler.h"

Define_Module(Flexi_OBS_BurstDisassembler);

Flexi_OBS_BurstDisassembler::~Flexi_OBS_BurstDisassembler(){
    if(endToEndAckEnabled)
        cancelAndDelete(cleanPendingAckTimer);
}

void Flexi_OBS_BurstDisassembler::initialize(int stage){
    if(stage == 0){
        lostBurstId = registerSignal("lostBurst");
        lostBCPId = registerSignal("lostBCP");
        successfulBurstId = registerSignal("successfulBurst");

        endToEndAckEnabled = par("endToEndAckEnabled");
        updateRoutingTable = par("updateRoutingTable");

        bcpSources.setName("message senders");

        if(endToEndAckEnabled)
        {
            cleanPendingAckTimer = new cMessage("pendingAckCleaner");
            scheduleAt(simTime()+10, cleanPendingAckTimer);
        }

        recvBursts = 0;
        recvBcps = 0;
        recvControls = 0;
        burstLostByImpairments = 0;
        burstLost = 0;
        pendingAcksSize = 0;

        WATCH(recvBcps);
        WATCH(recvControls);
        WATCH(recvBursts);
        WATCH(burstLost);
        WATCH(burstLostByImpairments);
        WATCH(pendingAcksSize);
        WATCH_VECTOR(pendingAcks);
        table = check_and_cast<Flexi_OBS_EdgeRoutingTable*>(getParentModule()->getSubmodule("EdgeRoutingTable"));
    }

    if(stage == 3){
        ipAddr = (check_and_cast<K_ShortestPathTable *>(this->getParentModule()->getParentModule()->getSubmodule("k_ShortestPathTable")))->getTop(0, false)->getSrcAddress();
        WATCH(ipAddr);
    }
}

void Flexi_OBS_BurstDisassembler::handleMessage(cMessage *msg){
    if(msg->isSelfMessage())
    {
        if(strcmp(msg->getName(), "pendingAckCleaner") ==0) {
            int last = 0;
            for(int i = 0; i < pendingAcks.size(); i++){
                EndToEndAck* ack = check_and_cast<EndToEndAck*>(pendingAcks[i]);
                if((simTime() - ack->getCreationTime())  > 4)
                    last = i+1;
                else break;
            }

            if(last > 0){
                for(int i=0; i < last; i++)
                {
                    EndToEndAck* e = pendingAcks[i];
                    delete e;
                }
                pendingAcks.erase(pendingAcks.begin(), pendingAcks.begin()+last);
                pendingAcksSize = pendingAcks.size();
            }

            scheduleAt(simTime()+10, cleanPendingAckTimer);
        }

        return;
    }

    Flexi_OBS_DisassemblerInfo* info = new Flexi_OBS_DisassemblerInfo();
    info->setEntryPort(msg->getArrivalGate()->getPreviousGate()->getPreviousGate()->getId());
    info->setIpAddress(ipAddr);

    if(strcmp(msg->getName(), "BCP") ==0) {
        Flexi_OBS_BurstControlPacket* bcp = check_and_cast<Flexi_OBS_BurstControlPacket*>(msg);
        if(doOnBCPArrival(bcp, info)) return;
        recvControls++;
        recvBcps++;
        int srcAddr = bcp->getSrcAddr();
        bcpSources.record(srcAddr);
        addPendingAck(bcp, info);

        int pos = -1;
        bool found =  false;
        string src = std::to_string(srcAddr);
        for(Counter obj : sourceCounter)
        {
            pos++;
            if(strcmp(obj.description.c_str(), src.c_str()) == 0)
            {
                found = true;
                break;
            }
        }

        if(pos > -1 && found)
            sourceCounter[pos].count++;
        else
        {
            Counter counter;
            counter.description = src;
            counter.count = 1;
            sourceCounter.push_back(counter);
        }

        delete msg;
        return;
    }

    if(strcmp(msg->getName(), "burst") == 0)
    {
        OBS_Burst* burst = check_and_cast<OBS_Burst*>(msg);

        if(burst->getIsReadable()){
            if(doOnBurstArrival(burst, info)) return;
            recvBursts++;
            emit(successfulBurstId, true);
            sendPendingAck(burst, true);
            delete info;
        }else{
            burstLostByImpairments++;
            burstLost++;
            emit(lostBurstId, 3);
            sendPendingAck(burst, false);
            delete info;
        }

        delete msg;
        return;
    }

    handleControlMessage(msg, info);
}

void Flexi_OBS_BurstDisassembler::finish(){
    recordScalar("burst lost",burstLost);
    recordScalar("burst lost due to impairments", burstLostByImpairments);
    recordScalar("received Bursts",recvBursts);
    recordScalar("received BCP", recvBcps);
    recordScalar("received control messages", recvControls);

    for(Counter obj : sourceCounter)
    {
        recordScalar(("source:" + obj.description.str()).c_str(), obj.count);
    }

}

Flexi_OBS_Routing* Flexi_OBS_BurstDisassembler::getRouter()
{
    return check_and_cast<Flexi_OBS_Routing*>(this->getParentModule()->getModuleByPath(".assembler.router"));
}

void Flexi_OBS_BurstDisassembler::handleControlMessage(cMessage* msg, Flexi_OBS_DisassemblerInfo* info)
{
    if(strcmp(msg->getName(),"failedBcpAck") == 0 || strcmp(msg->getName(),"successfulBcpAck") == 0 || strcmp(msg->getName(),"ANT") == 0 || strcmp(msg->getName(),"traversalAck") == 0)
    {
        if(strcmp(msg->getName(),"ANT") == 0)
        {
            Flexi_OBS_BurstControlPacket* bcp = check_and_cast<Flexi_OBS_BurstControlPacket*>(msg);
            if(bcp->getDestAddr() != ipAddr){
                delete msg;
                return;
            }
        }

        msg->removeControlInfo();
        msg->setControlInfo(info);
        recvControls++;

        doUpdateRoutingTable(msg);
    }
}

void Flexi_OBS_BurstDisassembler::sendPendingAck(OBS_Burst* burst, bool isSuccessful)
{
    //send EndToEndAck
    for(int i = 0; i < pendingAcks.size(); i++)
    {
        if(pendingAcks[i]->getNumSeq() == burst->getNumSeq() && pendingAcks[i]->getBurstifierId() == burst->getBurstifierId())
        {
            if(!isSuccessful) pendingAcks[i]->setName("failedBcpAck");
            sendDirect(pendingAcks[i], getRouter(), "internalComm");
            pendingAcks.erase(pendingAcks.begin()+i);
            pendingAcksSize--;
            break;
        }
    }
}

void Flexi_OBS_BurstDisassembler::doUpdateRoutingTable(cMessage* msg)
{
    if(updateRoutingTable)
        sendDirect(msg, table, "ackIn");
    else delete(msg);
}

void Flexi_OBS_BurstDisassembler::addPendingAck(Flexi_OBS_BurstControlPacket* bcp, Flexi_OBS_DisassemblerInfo* info)
{
    if(endToEndAckEnabled){
        EndToEndAck* ack = new EndToEndAck("successfulBcpAck");
        ack->setBurstifierId(bcp->getBurstifierId());
        ack->setNumSeq(bcp->getNumSeq());
        ack->setSenderId(bcp->getSrcAddr());
        ack->setSchedulingPriority(2);

        if(bcp->getRecordPath()){
            ack->setEntryIdsArraySize(bcp->getPathPos());
            for(int i =0; i < bcp->getPathPos(); i++)
                ack->setEntryIds(i, bcp->getEntryIds(i));

            ack->setEntryIdPos(bcp->getPathPos());
            ack->setControlInfo(info);
        }else ack->setEntry_Id(bcp->getEntryId());

        ack->setRoute(bcp->getRoute());
        ack->setRoutePos(bcp->getRoutePos()-1);
        ack->setShortestPathCost(bcp->getShortestPathCost());
        ack->setDistTravelled(bcp->getDistTravelled());
        ack->setNodeCounter(bcp->getNodeCounter());
        pendingAcks.push_back(ack);
        pendingAcksSize++;
    }
}

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

#include "Flexi_OBS_OpticalCrossConnect.h"

Define_Module(Flexi_OBS_OpticalCrossConnect);

Flexi_OBS_OpticalCrossConnect::Flexi_OBS_OpticalCrossConnect() {
    // TODO Auto-generated constructor stub

}

Flexi_OBS_OpticalCrossConnect::~Flexi_OBS_OpticalCrossConnect() {
    // TODO Auto-generated destructor stub
}

void Flexi_OBS_OpticalCrossConnect::initialize(int stage)
{
    if(stage == 0){
        burstSent = 0;
        bcpSent = 0;
        controlSent = 0;
        processingDelay = par("BCPProcessingDelay");
        switchingDelay = par("switchingDelay");
        lostBurstId = registerSignal("lostBurst");
        reservationsCounter = 0;
        WATCH(reservationsCounter);
    }else if(stage == 1){
        int outBaseId = gateBaseId("out");
        int size = gateSize("out");

        for(int i =0; i < size; i++)
        {
            cGate* outGate = gate(outBaseId+i);
            cModule* mod  = outGate->getOwnerModule();

            do{
                outGate = outGate->getNextGate();
                mod  = outGate->getOwnerModule();

                if(strstr(mod->getName(), "edgeNode"))
                {
                    toEdgeNodeGateId = outBaseId+i;
                    break;
                }

            }while(!(strstr(mod->getName(), "leftMux") || strstr(mod->getName(), "rightMux")));

            if(!(strstr(mod->getName(), "edgeNode")))
            links[outBaseId+i] = check_and_cast<Flexi_OBS_BurstMux*>(mod);
        }
    }
}

void Flexi_OBS_OpticalCrossConnect::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        for(int i = 0; i < reservations.size(); i++)
        {
            int burstifierId = msg->par("burstifierId");
            int numseq = msg->par("numseq");
            if((reservations[i].burstifierId == burstifierId && reservations[i].numseq == numseq))
            {
                reservations[i].ready = true;
                delete(msg);
                return;
            }
        }
    }

    OBS_Burst *burst = dynamic_cast<OBS_Burst *> (msg);

    Flexi_OBS_BurstControlPacket *bcp = dynamic_cast<Flexi_OBS_BurstControlPacket *>(msg);

    EndToEndAck* e = dynamic_cast<EndToEndAck*>(msg);

    if(burst != NULL){
        Flexi_OBS_BurstRouterInfo *info = check_and_cast<Flexi_OBS_BurstRouterInfo *> (msg->getControlInfo());

        for(int i = 0; i < reservations.size(); i++)
        {
            if(reservations[i].msgId == msg->getId() && reservations[i].burstifierId == burst->getBurstifierId() && reservations[i].numseq == burst->getNumSeq() && reservations[i].ready)
            {
                if(reservations[i].sendDelayed)
                    sendDelayed(msg, reservations[i].delay, reservations[i].link);
                else send(msg, reservations[i].link);

                reservations.erase(reservations.begin()+i);
                reservationsCounter = reservations.size();
                burstSent++;
                return;
            }else if (reservations[i].destLabel == info->getLabel() && reservations[i].ready){
                if(reservations[i].sendDelayed)
                    sendDelayed(msg, reservations[i].delay, reservations[i].link);
                else send(msg, reservations[i].link);

                burstSent++;
                return;
            }
        }

        emit(lostBurstId, 1);
    }else if(bcp != NULL){
        for(int i = 0; i < reservations.size(); i++)
        {
            if((reservations[i].msgId == bcp->getBurstId() && reservations[i].burstifierId == bcp->getBurstifierId() && reservations[i].numseq == bcp->getNumSeq()))
            {
                send(msg, reservations[i].link);
                controlSent++;
                bcpSent++;
                return;
            }
        }
    }else if(e != NULL){
        for(int i = 0; i < reservations.size(); i++)
        {
            if((reservations[i].msgId == e->getId() && reservations[i].burstifierId == e->getBurstifierId() && reservations[i].numseq == e->getNumSeq()))
            {
                send(msg, reservations[i].link);
                reservations.erase(reservations.begin()+i);
                reservationsCounter = reservations.size();
                controlSent++;
                return;
            }
        }
    }

    delete(msg);
}

void Flexi_OBS_OpticalCrossConnect::setOutLink(long msgId, int seq, int burstifierId, int link)
{
    //    for(int i = 0; i < reservations.size(); i++)
    //    {
    //        if(reservations[i].numseq == seq && reservations[i].burstifierId == burstifierId)
    //        {
    //            reservations[i].link = link;
    //            return;
    //        }
    //    }

    Enter_Method_Silent();
    reservation reserve;
    reserve.burstifierId = burstifierId;
    reserve.numseq = seq;
    reserve.link = link;
    reserve.ready = false;
    reserve.sendDelayed = false;
    reserve.msgId = msgId;

    reservations.push_back(reserve);
    reservationsCounter = reservations.size();

    if(switchingDelay > 0){
        cMessage *msg = new cMessage("switchready");
        msg->addPar("burstifierId").setLongValue(burstifierId);
        msg->addPar("numseq").setLongValue(seq);
        msg->addPar("msgId").setLongValue(msgId);
        scheduleAt(simTime() + processingDelay + switchingDelay, msg);
    }
}

void Flexi_OBS_OpticalCrossConnect::setOutLink(long msgId, int seq, int burstifierId, int link, simtime_t delay)
{
    Enter_Method_Silent();
    reservation reserve;
    reserve.burstifierId = burstifierId;
    reserve.numseq = seq;
    reserve.link = link;
    reserve.ready = false;
    reserve.sendDelayed = true;
    reserve.delay = delay;
    reserve.msgId = msgId;

    reservations.push_back(reserve);
    reservationsCounter = reservations.size();

    if(switchingDelay > 0){
        cMessage *msg = new cMessage("switchready");
        msg->addPar("burstifierId").setLongValue(burstifierId);
        msg->addPar("numseq").setLongValue(seq);
        msg->addPar("msgId").setLongValue(msgId);
        scheduleAt(simTime() + processingDelay + switchingDelay, msg);
    }
}

void Flexi_OBS_OpticalCrossConnect::releaseOutLink(long msgId, int seq, int burstifierId)
{
    for(int i = reservations.size()-1; i >=0 ; i--)
    {
        if(reservations[i].msgId == msgId && reservations[i].numseq == seq && reservations[i].burstifierId == burstifierId){
            reservations.erase(reservations.begin() + i);
            reservationsCounter = reservations.size();
        }
    }
}

void Flexi_OBS_OpticalCrossConnect::releaseOutLink(int seq, int burstifierId)
{
    for(int i = reservations.size()-1; i >=0 ; i--)
    {
        if(reservations[i].numseq == seq && reservations[i].burstifierId == burstifierId){
            reservations.erase(reservations.begin() + i);
            reservationsCounter = reservations.size();
        }
    }
}

void Flexi_OBS_OpticalCrossConnect::finish()
{
    recordScalar("control message sent", controlSent);
    recordScalar("burst sent", burstSent);
    recordScalar("bcp sent", bcpSent);
}

Flexi_OBS_BurstMux* Flexi_OBS_OpticalCrossConnect::getMux(int gateId)
{
    return links[gateId];
}

int Flexi_OBS_OpticalCrossConnect::getEdgeNodeGateId()
{
    return toEdgeNodeGateId;
}

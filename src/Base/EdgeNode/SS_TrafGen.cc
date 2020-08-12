//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004-2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "SS_TrafGen.h"

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/contract/IL3AddressType.h"


Define_Module(SS_TrafGen);

SS_TrafGen::SS_TrafGen()
{
}

SS_TrafGen::~SS_TrafGen()
{
}

void SS_TrafGen::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        int protocolId = par("protocol");
        if (protocolId < 143 || protocolId > 254)
            throw cRuntimeError("invalid protocol id %d, accepts only between 143 and 254", protocolId);
        protocol = ProtocolGroup::ipprotocol.findProtocol(protocolId);
        if (!protocol) {
            std::string name = "prot_" + std::to_string(protocolId);
            protocol = new Protocol(name.c_str(), name.c_str());
            allocatedProtocols.push_back(protocol);
            ProtocolGroup::ipprotocol.addProtocol(protocolId, protocol);
        }
        numPackets = par("numPackets");
        startTime = par("startTime");
        stopTime = par("stopTime");
        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");

        packetLengthPar = &par("packetLength");
        H = par("H");
        meanSendInterval = par("meanSendInterval");
        alpha2 = 7.7929 * log(H) + 4.9513;

        timer = new cMessage("sendTimer");

        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        registerService(*protocol, nullptr, gate("ipIn"));
        registerProtocol(*protocol, gate("ipOut"), nullptr);
    }
}

void SS_TrafGen::scheduleNextPacket(simtime_t previous)
{
    simtime_t next;
    if (previous == -1) {
        next = simTime() <= startTime ? startTime : simTime();
        timer->setKind(START);
    }
    else {
        next = previous + getExponentialSendInterval(generateSSNumber());
        timer->setKind(NEXT);
    }
    if (stopTime < SIMTIME_ZERO || next < stopTime)
        scheduleAt(next, timer);
}

double SS_TrafGen::generateSSNumber()
{
    double A1 = beta(alpha1, alpha2);
    double A2 = beta(alpha1, alpha2);
    double Y1 = normal(0, 1);
    double Y2 = normal(0, 1);

    Z1 = A1*Z1 + Y1;
    Z2 = A2*Z2 + Y2;

    return Z1 + Z2;
}

double SS_TrafGen::getExponentialSendInterval(double a)
{
//    double b0 = 0.2316419, b1 = 0.319381530, b2 = -0.356563782, b3 = 1.781477937, b4 = -1.821255978, b5 = 1.330274429;
//    double t = 1.0/(1.0 + (b0*a));
//    double pdf = 1.0/(sqrt(2.0*PI) * (-0.5*pow(a,2.0)));
//    N1 = 1.0-(pdf*((b1*t)+(b2*pow(t,2.0))+(b3*pow(t,3.0))+(b4*pow(t,4.0))+(b5*pow(t,5.0))));
    N2 = 0.5*erfc((-1.0*a)/sqrt(2));
    double N = 0.5 + 0.5*erf(a/sqrt(2));
    return (-1.0*meanSendInterval)*log(N);
}

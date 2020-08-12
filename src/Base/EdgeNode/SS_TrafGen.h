//
// Copyright (C) 2004 Andras Varga
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
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

#ifndef __OBSMODULES_SS_TRAFGEN_H_
#define __OBSMODULES_SS_TRAFGEN_H_

#include <vector>

#include "inet/applications/generic/IpvxTrafGen.h"
#include "inet/applications/generic/IpvxTrafSink.h"
#include "inet/common/INETDefs.h"
#include "inet/common/Protocol.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/L3Address.h"

using namespace omnetpp;
using namespace inet;

/**
 * IP traffic generator application. See NED for more info.
 */
class SS_TrafGen : public IpvxTrafGen
{
  protected:
    double alpha1 = 1.0, alpha2, Z1 = 0, Z2 = 0;
    double H, meanSendInterval, N2;

    virtual void scheduleNextPacket(simtime_t previous);
    virtual void initialize(int stage) override;
    virtual double generateSSNumber();
    virtual double getExponentialSendInterval(double a);

  public:
    //const double pi = 3.141592653589793;
    SS_TrafGen();
    virtual ~SS_TrafGen();
};

#endif


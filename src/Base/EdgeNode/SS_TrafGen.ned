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

package flexi_obsmodules.src.Base.EdgeNode;

import inet.applications.generic.IIpvxTrafficGenerator;
//
// TODO auto-generated module
//
simple SS_TrafGen like IIpvxTrafficGenerator
{
    parameters:
        double startTime @unit(s) = default(1s); // time of sending the first packet
        double stopTime @unit(s) = default(-1s);  // time of finishing sending, negative values mean forever
        int numPackets = default(-1); // max number of packets to generate, -1 means forever
        int protocol; // value for IPv4, IPv6 protocol field, accepts only between 143 and 254
        volatile int packetLength @unit(B); // packet length in bytes
        string destAddresses = default(""); // list of destination addresses, separated by spaces
        
        double H = default(0.9);
        double meanSendInterval @unit("s") = default(0.05ms)
        @lifecycleSupport;
        @display("i=block/source");
        @signal[packetSent](type=inet::Packet);
        @signal[packetReceived](type=inet::Packet);
        @statistic[packetReceived](title="packets received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[packetSent](title="packets sent"; source=packetSent; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="dataAge(packetReceived)"; unit=s; record=histogram,vector; interpolationmode=none);
    gates:
        input ipIn @labels(Ipv4ControlInfo/up,Ipv6ControlInfo/up);
        output ipOut @labels(Ipv4ControlInfo/down,Ipv6ControlInfo/down);
}


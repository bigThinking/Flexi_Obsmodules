//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/messages/OBS_Burst.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __OBS_BURST_M_H
#define __OBS_BURST_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
 
    #include "TransmittedMessage_m.h"
    using namespace omnetpp;
     
// }}

/**
 * Class generated from <tt>src/Base/messages/OBS_Burst.msg:33</tt> by nedtool.
 * <pre>
 * // Burst message. Contains a message queue and stores info such as the burst Id (using OMNeT's id() function), number of packets, offsets and destination label.
 * // This message is extended by the OBS_Burst class (OBS_Burst.cc and .h) which implements methods to access the message queue.
 * packet OBS_Burst extends TransmittedMessage_Base
 * {
 *     \@customize(true); //Use this to extend this message with a subclass
 *     cQueue messages; //Message queue
 *     int numPackets = -1; //Number of packets inside the burst
 *     simtime_t minOffset = -1; //Minimum offset between BCP and Burst
 *     simtime_t maxOffset = -1; //Maximum offset between BCP and burst  
 *     int burstifierId = -1; //Burstifier id
 *     int numSeq = -1; //Sequence number into burst sender
 *     int senderId = -1; //Burst sender identifier. Should not be used as Id
 *     bool hasBeenTransmitted = false;
 * }
 * </pre>
 *
 * OBS_Burst_Base is only useful if it gets subclassed, and OBS_Burst is derived from it.
 * The minimum code to be written for OBS_Burst is the following:
 *
 * <pre>
 * class OBS_Burst : public OBS_Burst_Base
 * {
 *   private:
 *     void copy(const OBS_Burst& other) { ... }

 *   public:
 *     OBS_Burst(const char *name=nullptr, short kind=0) : OBS_Burst_Base(name,kind) {}
 *     OBS_Burst(const OBS_Burst& other) : OBS_Burst_Base(other) {copy(other);}
 *     OBS_Burst& operator=(const OBS_Burst& other) {if (this==&other) return *this; OBS_Burst_Base::operator=(other); copy(other); return *this;}
 *     virtual OBS_Burst *dup() const override {return new OBS_Burst(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from OBS_Burst_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(OBS_Burst)
 * </pre>
 */
class OBS_Burst_Base : public ::TransmittedMessage_Base
{
  protected:
    cQueue messages;
    int numPackets;
    ::omnetpp::simtime_t minOffset;
    ::omnetpp::simtime_t maxOffset;
    int burstifierId;
    int numSeq;
    int senderId;
    bool hasBeenTransmitted;

  private:
    void copy(const OBS_Burst_Base& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OBS_Burst_Base&);
    // make constructors protected to avoid instantiation
    OBS_Burst_Base(const char *name=nullptr, short kind=0);
    OBS_Burst_Base(const OBS_Burst_Base& other);
    // make assignment operator protected to force the user override it
    OBS_Burst_Base& operator=(const OBS_Burst_Base& other);

  public:
    virtual ~OBS_Burst_Base();
    virtual OBS_Burst_Base *dup() const override {throw omnetpp::cRuntimeError("You forgot to manually add a dup() function to class OBS_Burst");}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual cQueue& getMessages();
    virtual const cQueue& getMessages() const {return const_cast<OBS_Burst_Base*>(this)->getMessages();}
    virtual void setMessages(const cQueue& messages);
    virtual int getNumPackets() const;
    virtual void setNumPackets(int numPackets);
    virtual ::omnetpp::simtime_t getMinOffset() const;
    virtual void setMinOffset(::omnetpp::simtime_t minOffset);
    virtual ::omnetpp::simtime_t getMaxOffset() const;
    virtual void setMaxOffset(::omnetpp::simtime_t maxOffset);
    virtual int getBurstifierId() const;
    virtual void setBurstifierId(int burstifierId);
    virtual int getNumSeq() const;
    virtual void setNumSeq(int numSeq);
    virtual int getSenderId() const;
    virtual void setSenderId(int senderId);
    virtual bool getHasBeenTransmitted() const;
    virtual void setHasBeenTransmitted(bool hasBeenTransmitted);
};


#endif // ifndef __OBS_BURST_M_H


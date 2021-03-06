//
// Generated file, do not edit! Created by nedtool 5.4 from src/Base/messages/OBS_BurstifierInfo.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __OBS_BURSTIFIERINFO_M_H
#define __OBS_BURSTIFIERINFO_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0504
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>src/Base/messages/OBS_BurstifierInfo.msg:23</tt> by nedtool.
 * <pre>
 * // Additional burst control info included in OBS_PacketBurstifier and OBS_FileBurstifier.
 * class OBS_BurstifierInfo
 * {
 *     int label = -1; // Destination label.
 * }
 * </pre>
 */
class OBS_BurstifierInfo : public ::omnetpp::cObject
{
  protected:
    int label;

  private:
    void copy(const OBS_BurstifierInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OBS_BurstifierInfo&);

  public:
    OBS_BurstifierInfo();
    OBS_BurstifierInfo(const OBS_BurstifierInfo& other);
    virtual ~OBS_BurstifierInfo();
    OBS_BurstifierInfo& operator=(const OBS_BurstifierInfo& other);
    virtual OBS_BurstifierInfo *dup() const override {return new OBS_BurstifierInfo(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getLabel() const;
    virtual void setLabel(int label);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const OBS_BurstifierInfo& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, OBS_BurstifierInfo& obj) {obj.parsimUnpack(b);}


#endif // ifndef __OBS_BURSTIFIERINFO_M_H


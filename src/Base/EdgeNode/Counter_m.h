//
// Generated file, do not edit! Created by nedtool 5.4 from src/Base/EdgeNode/Counter.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __COUNTER_M_H
#define __COUNTER_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0504
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Struct generated from src/Base/EdgeNode/Counter.msg:16 by nedtool.
 */
struct Counter
{
    Counter();
    ::omnetpp::opp_string description;
    int count;
};

// helpers for local use
void __doPacking(omnetpp::cCommBuffer *b, const Counter& a);
void __doUnpacking(omnetpp::cCommBuffer *b, Counter& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Counter& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Counter& obj) { __doUnpacking(b, obj); }


#endif // ifndef __COUNTER_M_H


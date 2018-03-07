//
// Generated file, do not edit! Created by nedtool 5.1 from src/Base/messages/EndToEndAck.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "EndToEndAck_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(EndToEndAck)

EndToEndAck::EndToEndAck(const char *name, short kind) : ::TransmittedMessage_Base(name,kind)
{
    this->setByteLength(60);
    this->setIsControl(true);

    this->routePos = 0;
    this->burstifierId = -1;
    this->numSeq = -1;
    this->senderId = -1;
    this->entry_Id = 0;
    entryIds_arraysize = 0;
    this->entryIds = 0;
    this->entryIdPos = 0;
    this->shortestPathCost = 0;
    this->distTravelled = 0;
    this->nodeCounter = 0;
}

EndToEndAck::EndToEndAck(const EndToEndAck& other) : ::TransmittedMessage_Base(other)
{
    entryIds_arraysize = 0;
    this->entryIds = 0;
    copy(other);
}

EndToEndAck::~EndToEndAck()
{
    delete [] this->entryIds;
}

EndToEndAck& EndToEndAck::operator=(const EndToEndAck& other)
{
    if (this==&other) return *this;
    ::TransmittedMessage_Base::operator=(other);
    copy(other);
    return *this;
}

void EndToEndAck::copy(const EndToEndAck& other)
{
    this->route = other.route;
    this->routePos = other.routePos;
    this->burstifierId = other.burstifierId;
    this->numSeq = other.numSeq;
    this->senderId = other.senderId;
    this->entry_Id = other.entry_Id;
    delete [] this->entryIds;
    this->entryIds = (other.entryIds_arraysize==0) ? nullptr : new int[other.entryIds_arraysize];
    entryIds_arraysize = other.entryIds_arraysize;
    for (unsigned int i=0; i<entryIds_arraysize; i++)
        this->entryIds[i] = other.entryIds[i];
    this->entryIdPos = other.entryIdPos;
    this->shortestPathCost = other.shortestPathCost;
    this->distTravelled = other.distTravelled;
    this->nodeCounter = other.nodeCounter;
}

void EndToEndAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::TransmittedMessage_Base::parsimPack(b);
    doParsimPacking(b,this->route);
    doParsimPacking(b,this->routePos);
    doParsimPacking(b,this->burstifierId);
    doParsimPacking(b,this->numSeq);
    doParsimPacking(b,this->senderId);
    doParsimPacking(b,this->entry_Id);
    b->pack(entryIds_arraysize);
    doParsimArrayPacking(b,this->entryIds,entryIds_arraysize);
    doParsimPacking(b,this->entryIdPos);
    doParsimPacking(b,this->shortestPathCost);
    doParsimPacking(b,this->distTravelled);
    doParsimPacking(b,this->nodeCounter);
}

void EndToEndAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::TransmittedMessage_Base::parsimUnpack(b);
    doParsimUnpacking(b,this->route);
    doParsimUnpacking(b,this->routePos);
    doParsimUnpacking(b,this->burstifierId);
    doParsimUnpacking(b,this->numSeq);
    doParsimUnpacking(b,this->senderId);
    doParsimUnpacking(b,this->entry_Id);
    delete [] this->entryIds;
    b->unpack(entryIds_arraysize);
    if (entryIds_arraysize==0) {
        this->entryIds = 0;
    } else {
        this->entryIds = new int[entryIds_arraysize];
        doParsimArrayUnpacking(b,this->entryIds,entryIds_arraysize);
    }
    doParsimUnpacking(b,this->entryIdPos);
    doParsimUnpacking(b,this->shortestPathCost);
    doParsimUnpacking(b,this->distTravelled);
    doParsimUnpacking(b,this->nodeCounter);
}

pathPtr& EndToEndAck::getRoute()
{
    return this->route;
}

void EndToEndAck::setRoute(const pathPtr& route)
{
    this->route = route;
}

int EndToEndAck::getRoutePos() const
{
    return this->routePos;
}

void EndToEndAck::setRoutePos(int routePos)
{
    this->routePos = routePos;
}

int EndToEndAck::getBurstifierId() const
{
    return this->burstifierId;
}

void EndToEndAck::setBurstifierId(int burstifierId)
{
    this->burstifierId = burstifierId;
}

int EndToEndAck::getNumSeq() const
{
    return this->numSeq;
}

void EndToEndAck::setNumSeq(int numSeq)
{
    this->numSeq = numSeq;
}

int EndToEndAck::getSenderId() const
{
    return this->senderId;
}

void EndToEndAck::setSenderId(int senderId)
{
    this->senderId = senderId;
}

int EndToEndAck::getEntry_Id() const
{
    return this->entry_Id;
}

void EndToEndAck::setEntry_Id(int entry_Id)
{
    this->entry_Id = entry_Id;
}

void EndToEndAck::setEntryIdsArraySize(unsigned int size)
{
    int *entryIds2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = entryIds_arraysize < size ? entryIds_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        entryIds2[i] = this->entryIds[i];
    for (unsigned int i=sz; i<size; i++)
        entryIds2[i] = 0;
    entryIds_arraysize = size;
    delete [] this->entryIds;
    this->entryIds = entryIds2;
}

unsigned int EndToEndAck::getEntryIdsArraySize() const
{
    return entryIds_arraysize;
}

int EndToEndAck::getEntryIds(unsigned int k) const
{
    if (k>=entryIds_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", entryIds_arraysize, k);
    return this->entryIds[k];
}

void EndToEndAck::setEntryIds(unsigned int k, int entryIds)
{
    if (k>=entryIds_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", entryIds_arraysize, k);
    this->entryIds[k] = entryIds;
}

int EndToEndAck::getEntryIdPos() const
{
    return this->entryIdPos;
}

void EndToEndAck::setEntryIdPos(int entryIdPos)
{
    this->entryIdPos = entryIdPos;
}

int EndToEndAck::getShortestPathCost() const
{
    return this->shortestPathCost;
}

void EndToEndAck::setShortestPathCost(int shortestPathCost)
{
    this->shortestPathCost = shortestPathCost;
}

int EndToEndAck::getDistTravelled() const
{
    return this->distTravelled;
}

void EndToEndAck::setDistTravelled(int distTravelled)
{
    this->distTravelled = distTravelled;
}

int EndToEndAck::getNodeCounter() const
{
    return this->nodeCounter;
}

void EndToEndAck::setNodeCounter(int nodeCounter)
{
    this->nodeCounter = nodeCounter;
}

class EndToEndAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EndToEndAckDescriptor();
    virtual ~EndToEndAckDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EndToEndAckDescriptor)

EndToEndAckDescriptor::EndToEndAckDescriptor() : omnetpp::cClassDescriptor("EndToEndAck", "TransmittedMessage_Base")
{
    propertynames = nullptr;
}

EndToEndAckDescriptor::~EndToEndAckDescriptor()
{
    delete[] propertynames;
}

bool EndToEndAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EndToEndAck *>(obj)!=nullptr;
}

const char **EndToEndAckDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EndToEndAckDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EndToEndAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount() : 11;
}

unsigned int EndToEndAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *EndToEndAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "route",
        "routePos",
        "burstifierId",
        "numSeq",
        "senderId",
        "entry_Id",
        "entryIds",
        "entryIdPos",
        "shortestPathCost",
        "distTravelled",
        "nodeCounter",
    };
    return (field>=0 && field<11) ? fieldNames[field] : nullptr;
}

int EndToEndAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "route")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "routePos")==0) return base+1;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstifierId")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "numSeq")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderId")==0) return base+4;
    if (fieldName[0]=='e' && strcmp(fieldName, "entry_Id")==0) return base+5;
    if (fieldName[0]=='e' && strcmp(fieldName, "entryIds")==0) return base+6;
    if (fieldName[0]=='e' && strcmp(fieldName, "entryIdPos")==0) return base+7;
    if (fieldName[0]=='s' && strcmp(fieldName, "shortestPathCost")==0) return base+8;
    if (fieldName[0]=='d' && strcmp(fieldName, "distTravelled")==0) return base+9;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeCounter")==0) return base+10;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EndToEndAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "pathPtr",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : nullptr;
}

const char **EndToEndAckDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EndToEndAckDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EndToEndAckDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EndToEndAck *pp = (EndToEndAck *)object; (void)pp;
    switch (field) {
        case 6: return pp->getEntryIdsArraySize();
        default: return 0;
    }
}

const char *EndToEndAckDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EndToEndAck *pp = (EndToEndAck *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EndToEndAckDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EndToEndAck *pp = (EndToEndAck *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRoute(); return out.str();}
        case 1: return long2string(pp->getRoutePos());
        case 2: return long2string(pp->getBurstifierId());
        case 3: return long2string(pp->getNumSeq());
        case 4: return long2string(pp->getSenderId());
        case 5: return long2string(pp->getEntry_Id());
        case 6: return long2string(pp->getEntryIds(i));
        case 7: return long2string(pp->getEntryIdPos());
        case 8: return long2string(pp->getShortestPathCost());
        case 9: return long2string(pp->getDistTravelled());
        case 10: return long2string(pp->getNodeCounter());
        default: return "";
    }
}

bool EndToEndAckDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EndToEndAck *pp = (EndToEndAck *)object; (void)pp;
    switch (field) {
        case 1: pp->setRoutePos(string2long(value)); return true;
        case 2: pp->setBurstifierId(string2long(value)); return true;
        case 3: pp->setNumSeq(string2long(value)); return true;
        case 4: pp->setSenderId(string2long(value)); return true;
        case 5: pp->setEntry_Id(string2long(value)); return true;
        case 6: pp->setEntryIds(i,string2long(value)); return true;
        case 7: pp->setEntryIdPos(string2long(value)); return true;
        case 8: pp->setShortestPathCost(string2long(value)); return true;
        case 9: pp->setDistTravelled(string2long(value)); return true;
        case 10: pp->setNodeCounter(string2long(value)); return true;
        default: return false;
    }
}

const char *EndToEndAckDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(pathPtr));
        default: return nullptr;
    };
}

void *EndToEndAckDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EndToEndAck *pp = (EndToEndAck *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRoute()); break;
        default: return nullptr;
    }
}



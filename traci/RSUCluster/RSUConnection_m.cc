//
// Generated file, do not edit! Created by nedtool 5.6 from veins/modules/application/traci/RSUCluster/RSUConnection.msg.
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
#include "RSUConnection_m.h"

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

namespace veins {

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

Register_Class(RSUAdvertisement)

RSUAdvertisement::RSUAdvertisement(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->y = 0;
    this->x = 0;
    this->advertisementTime = 0;
}

RSUAdvertisement::RSUAdvertisement(const RSUAdvertisement& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

RSUAdvertisement::~RSUAdvertisement()
{
}

RSUAdvertisement& RSUAdvertisement::operator=(const RSUAdvertisement& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void RSUAdvertisement::copy(const RSUAdvertisement& other)
{
    this->RSUName = other.RSUName;
    this->y = other.y;
    this->x = other.x;
    this->senderMacAddr = other.senderMacAddr;
    this->advertisementTime = other.advertisementTime;
}

void RSUAdvertisement::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->RSUName);
    doParsimPacking(b,this->y);
    doParsimPacking(b,this->x);
    doParsimPacking(b,this->senderMacAddr);
    doParsimPacking(b,this->advertisementTime);
}

void RSUAdvertisement::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->RSUName);
    doParsimUnpacking(b,this->y);
    doParsimUnpacking(b,this->x);
    doParsimUnpacking(b,this->senderMacAddr);
    doParsimUnpacking(b,this->advertisementTime);
}

const char * RSUAdvertisement::getRSUName() const
{
    return this->RSUName.c_str();
}

void RSUAdvertisement::setRSUName(const char * RSUName)
{
    this->RSUName = RSUName;
}

int RSUAdvertisement::getY() const
{
    return this->y;
}

void RSUAdvertisement::setY(int y)
{
    this->y = y;
}

int RSUAdvertisement::getX() const
{
    return this->x;
}

void RSUAdvertisement::setX(int x)
{
    this->x = x;
}

LAddress::L2Type& RSUAdvertisement::getSenderMacAddr()
{
    return this->senderMacAddr;
}

void RSUAdvertisement::setSenderMacAddr(const LAddress::L2Type& senderMacAddr)
{
    this->senderMacAddr = senderMacAddr;
}

::omnetpp::simtime_t RSUAdvertisement::getAdvertisementTime() const
{
    return this->advertisementTime;
}

void RSUAdvertisement::setAdvertisementTime(::omnetpp::simtime_t advertisementTime)
{
    this->advertisementTime = advertisementTime;
}

class RSUAdvertisementDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RSUAdvertisementDescriptor();
    virtual ~RSUAdvertisementDescriptor();

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

Register_ClassDescriptor(RSUAdvertisementDescriptor)

RSUAdvertisementDescriptor::RSUAdvertisementDescriptor() : omnetpp::cClassDescriptor("veins::RSUAdvertisement", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

RSUAdvertisementDescriptor::~RSUAdvertisementDescriptor()
{
    delete[] propertynames;
}

bool RSUAdvertisementDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RSUAdvertisement *>(obj)!=nullptr;
}

const char **RSUAdvertisementDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RSUAdvertisementDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RSUAdvertisementDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int RSUAdvertisementDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *RSUAdvertisementDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "RSUName",
        "y",
        "x",
        "senderMacAddr",
        "advertisementTime",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int RSUAdvertisementDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RSUName")==0) return base+0;
    if (fieldName[0]=='y' && strcmp(fieldName, "y")==0) return base+1;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderMacAddr")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "advertisementTime")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RSUAdvertisementDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "int",
        "int",
        "LAddress::L2Type",
        "simtime_t",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **RSUAdvertisementDescriptor::getFieldPropertyNames(int field) const
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

const char *RSUAdvertisementDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int RSUAdvertisementDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RSUAdvertisement *pp = (RSUAdvertisement *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RSUAdvertisementDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RSUAdvertisement *pp = (RSUAdvertisement *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RSUAdvertisementDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RSUAdvertisement *pp = (RSUAdvertisement *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getRSUName());
        case 1: return long2string(pp->getY());
        case 2: return long2string(pp->getX());
        case 3: {std::stringstream out; out << pp->getSenderMacAddr(); return out.str();}
        case 4: return simtime2string(pp->getAdvertisementTime());
        default: return "";
    }
}

bool RSUAdvertisementDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RSUAdvertisement *pp = (RSUAdvertisement *)object; (void)pp;
    switch (field) {
        case 0: pp->setRSUName((value)); return true;
        case 1: pp->setY(string2long(value)); return true;
        case 2: pp->setX(string2long(value)); return true;
        case 4: pp->setAdvertisementTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *RSUAdvertisementDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 3: return omnetpp::opp_typename(typeid(LAddress::L2Type));
        default: return nullptr;
    };
}

void *RSUAdvertisementDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RSUAdvertisement *pp = (RSUAdvertisement *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getSenderMacAddr()); break;
        default: return nullptr;
    }
}

Register_Class(CARConnectionReq)

CARConnectionReq::CARConnectionReq(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
}

CARConnectionReq::CARConnectionReq(const CARConnectionReq& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

CARConnectionReq::~CARConnectionReq()
{
}

CARConnectionReq& CARConnectionReq::operator=(const CARConnectionReq& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void CARConnectionReq::copy(const CARConnectionReq& other)
{
    this->CarAddr = other.CarAddr;
}

void CARConnectionReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->CarAddr);
}

void CARConnectionReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->CarAddr);
}

LAddress::L2Type& CARConnectionReq::getCarAddr()
{
    return this->CarAddr;
}

void CARConnectionReq::setCarAddr(const LAddress::L2Type& CarAddr)
{
    this->CarAddr = CarAddr;
}

class CARConnectionReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CARConnectionReqDescriptor();
    virtual ~CARConnectionReqDescriptor();

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

Register_ClassDescriptor(CARConnectionReqDescriptor)

CARConnectionReqDescriptor::CARConnectionReqDescriptor() : omnetpp::cClassDescriptor("veins::CARConnectionReq", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

CARConnectionReqDescriptor::~CARConnectionReqDescriptor()
{
    delete[] propertynames;
}

bool CARConnectionReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CARConnectionReq *>(obj)!=nullptr;
}

const char **CARConnectionReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CARConnectionReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CARConnectionReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int CARConnectionReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *CARConnectionReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "CarAddr",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int CARConnectionReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CarAddr")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CARConnectionReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "LAddress::L2Type",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **CARConnectionReqDescriptor::getFieldPropertyNames(int field) const
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

const char *CARConnectionReqDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CARConnectionReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CARConnectionReq *pp = (CARConnectionReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CARConnectionReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CARConnectionReq *pp = (CARConnectionReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CARConnectionReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CARConnectionReq *pp = (CARConnectionReq *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getCarAddr(); return out.str();}
        default: return "";
    }
}

bool CARConnectionReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CARConnectionReq *pp = (CARConnectionReq *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *CARConnectionReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(LAddress::L2Type));
        default: return nullptr;
    };
}

void *CARConnectionReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CARConnectionReq *pp = (CARConnectionReq *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getCarAddr()); break;
        default: return nullptr;
    }
}

Register_Class(CARConnectionResp)

CARConnectionResp::CARConnectionResp(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->success = false;
}

CARConnectionResp::CARConnectionResp(const CARConnectionResp& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

CARConnectionResp::~CARConnectionResp()
{
}

CARConnectionResp& CARConnectionResp::operator=(const CARConnectionResp& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void CARConnectionResp::copy(const CARConnectionResp& other)
{
    this->RSUAddr = other.RSUAddr;
    this->success = other.success;
}

void CARConnectionResp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->RSUAddr);
    doParsimPacking(b,this->success);
}

void CARConnectionResp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->RSUAddr);
    doParsimUnpacking(b,this->success);
}

LAddress::L2Type& CARConnectionResp::getRSUAddr()
{
    return this->RSUAddr;
}

void CARConnectionResp::setRSUAddr(const LAddress::L2Type& RSUAddr)
{
    this->RSUAddr = RSUAddr;
}

bool CARConnectionResp::getSuccess() const
{
    return this->success;
}

void CARConnectionResp::setSuccess(bool success)
{
    this->success = success;
}

class CARConnectionRespDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CARConnectionRespDescriptor();
    virtual ~CARConnectionRespDescriptor();

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

Register_ClassDescriptor(CARConnectionRespDescriptor)

CARConnectionRespDescriptor::CARConnectionRespDescriptor() : omnetpp::cClassDescriptor("veins::CARConnectionResp", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

CARConnectionRespDescriptor::~CARConnectionRespDescriptor()
{
    delete[] propertynames;
}

bool CARConnectionRespDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CARConnectionResp *>(obj)!=nullptr;
}

const char **CARConnectionRespDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CARConnectionRespDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CARConnectionRespDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int CARConnectionRespDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *CARConnectionRespDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "RSUAddr",
        "success",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int CARConnectionRespDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RSUAddr")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "success")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CARConnectionRespDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "LAddress::L2Type",
        "bool",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **CARConnectionRespDescriptor::getFieldPropertyNames(int field) const
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

const char *CARConnectionRespDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CARConnectionRespDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CARConnectionResp *pp = (CARConnectionResp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CARConnectionRespDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CARConnectionResp *pp = (CARConnectionResp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CARConnectionRespDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CARConnectionResp *pp = (CARConnectionResp *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRSUAddr(); return out.str();}
        case 1: return bool2string(pp->getSuccess());
        default: return "";
    }
}

bool CARConnectionRespDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CARConnectionResp *pp = (CARConnectionResp *)object; (void)pp;
    switch (field) {
        case 1: pp->setSuccess(string2bool(value)); return true;
        default: return false;
    }
}

const char *CARConnectionRespDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(LAddress::L2Type));
        default: return nullptr;
    };
}

void *CARConnectionRespDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CARConnectionResp *pp = (CARConnectionResp *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRSUAddr()); break;
        default: return nullptr;
    }
}

Register_Class(CARDisconnectionReq)

CARDisconnectionReq::CARDisconnectionReq(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
}

CARDisconnectionReq::CARDisconnectionReq(const CARDisconnectionReq& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

CARDisconnectionReq::~CARDisconnectionReq()
{
}

CARDisconnectionReq& CARDisconnectionReq::operator=(const CARDisconnectionReq& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void CARDisconnectionReq::copy(const CARDisconnectionReq& other)
{
    this->CarName = other.CarName;
    this->CarAddr = other.CarAddr;
}

void CARDisconnectionReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->CarName);
    doParsimPacking(b,this->CarAddr);
}

void CARDisconnectionReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->CarName);
    doParsimUnpacking(b,this->CarAddr);
}

const char * CARDisconnectionReq::getCarName() const
{
    return this->CarName.c_str();
}

void CARDisconnectionReq::setCarName(const char * CarName)
{
    this->CarName = CarName;
}

LAddress::L2Type& CARDisconnectionReq::getCarAddr()
{
    return this->CarAddr;
}

void CARDisconnectionReq::setCarAddr(const LAddress::L2Type& CarAddr)
{
    this->CarAddr = CarAddr;
}

class CARDisconnectionReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CARDisconnectionReqDescriptor();
    virtual ~CARDisconnectionReqDescriptor();

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

Register_ClassDescriptor(CARDisconnectionReqDescriptor)

CARDisconnectionReqDescriptor::CARDisconnectionReqDescriptor() : omnetpp::cClassDescriptor("veins::CARDisconnectionReq", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

CARDisconnectionReqDescriptor::~CARDisconnectionReqDescriptor()
{
    delete[] propertynames;
}

bool CARDisconnectionReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CARDisconnectionReq *>(obj)!=nullptr;
}

const char **CARDisconnectionReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CARDisconnectionReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CARDisconnectionReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int CARDisconnectionReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *CARDisconnectionReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "CarName",
        "CarAddr",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int CARDisconnectionReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CarName")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CarAddr")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CARDisconnectionReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "LAddress::L2Type",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **CARDisconnectionReqDescriptor::getFieldPropertyNames(int field) const
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

const char *CARDisconnectionReqDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CARDisconnectionReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionReq *pp = (CARDisconnectionReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CARDisconnectionReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionReq *pp = (CARDisconnectionReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CARDisconnectionReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionReq *pp = (CARDisconnectionReq *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getCarName());
        case 1: {std::stringstream out; out << pp->getCarAddr(); return out.str();}
        default: return "";
    }
}

bool CARDisconnectionReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionReq *pp = (CARDisconnectionReq *)object; (void)pp;
    switch (field) {
        case 0: pp->setCarName((value)); return true;
        default: return false;
    }
}

const char *CARDisconnectionReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(LAddress::L2Type));
        default: return nullptr;
    };
}

void *CARDisconnectionReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionReq *pp = (CARDisconnectionReq *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getCarAddr()); break;
        default: return nullptr;
    }
}

Register_Class(CARDisconnectionResp)

CARDisconnectionResp::CARDisconnectionResp(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
}

CARDisconnectionResp::CARDisconnectionResp(const CARDisconnectionResp& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

CARDisconnectionResp::~CARDisconnectionResp()
{
}

CARDisconnectionResp& CARDisconnectionResp::operator=(const CARDisconnectionResp& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void CARDisconnectionResp::copy(const CARDisconnectionResp& other)
{
    this->RSUName = other.RSUName;
    this->RSUAddr = other.RSUAddr;
}

void CARDisconnectionResp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->RSUName);
    doParsimPacking(b,this->RSUAddr);
}

void CARDisconnectionResp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->RSUName);
    doParsimUnpacking(b,this->RSUAddr);
}

const char * CARDisconnectionResp::getRSUName() const
{
    return this->RSUName.c_str();
}

void CARDisconnectionResp::setRSUName(const char * RSUName)
{
    this->RSUName = RSUName;
}

LAddress::L2Type& CARDisconnectionResp::getRSUAddr()
{
    return this->RSUAddr;
}

void CARDisconnectionResp::setRSUAddr(const LAddress::L2Type& RSUAddr)
{
    this->RSUAddr = RSUAddr;
}

class CARDisconnectionRespDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CARDisconnectionRespDescriptor();
    virtual ~CARDisconnectionRespDescriptor();

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

Register_ClassDescriptor(CARDisconnectionRespDescriptor)

CARDisconnectionRespDescriptor::CARDisconnectionRespDescriptor() : omnetpp::cClassDescriptor("veins::CARDisconnectionResp", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

CARDisconnectionRespDescriptor::~CARDisconnectionRespDescriptor()
{
    delete[] propertynames;
}

bool CARDisconnectionRespDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CARDisconnectionResp *>(obj)!=nullptr;
}

const char **CARDisconnectionRespDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CARDisconnectionRespDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CARDisconnectionRespDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int CARDisconnectionRespDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *CARDisconnectionRespDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "RSUName",
        "RSUAddr",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int CARDisconnectionRespDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RSUName")==0) return base+0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RSUAddr")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CARDisconnectionRespDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "LAddress::L2Type",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **CARDisconnectionRespDescriptor::getFieldPropertyNames(int field) const
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

const char *CARDisconnectionRespDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CARDisconnectionRespDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionResp *pp = (CARDisconnectionResp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CARDisconnectionRespDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionResp *pp = (CARDisconnectionResp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CARDisconnectionRespDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionResp *pp = (CARDisconnectionResp *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getRSUName());
        case 1: {std::stringstream out; out << pp->getRSUAddr(); return out.str();}
        default: return "";
    }
}

bool CARDisconnectionRespDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionResp *pp = (CARDisconnectionResp *)object; (void)pp;
    switch (field) {
        case 0: pp->setRSUName((value)); return true;
        default: return false;
    }
}

const char *CARDisconnectionRespDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(LAddress::L2Type));
        default: return nullptr;
    };
}

void *CARDisconnectionRespDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CARDisconnectionResp *pp = (CARDisconnectionResp *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getRSUAddr()); break;
        default: return nullptr;
    }
}

Register_Class(RSUBeacon)

RSUBeacon::RSUBeacon(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
}

RSUBeacon::RSUBeacon(const RSUBeacon& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

RSUBeacon::~RSUBeacon()
{
}

RSUBeacon& RSUBeacon::operator=(const RSUBeacon& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void RSUBeacon::copy(const RSUBeacon& other)
{
    this->senderMacAddr = other.senderMacAddr;
    this->senderPos = other.senderPos;
    this->senderSpeed = other.senderSpeed;
}

void RSUBeacon::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->senderMacAddr);
    doParsimPacking(b,this->senderPos);
    doParsimPacking(b,this->senderSpeed);
}

void RSUBeacon::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->senderMacAddr);
    doParsimUnpacking(b,this->senderPos);
    doParsimUnpacking(b,this->senderSpeed);
}

LAddress::L2Type& RSUBeacon::getSenderMacAddr()
{
    return this->senderMacAddr;
}

void RSUBeacon::setSenderMacAddr(const LAddress::L2Type& senderMacAddr)
{
    this->senderMacAddr = senderMacAddr;
}

Coord& RSUBeacon::getSenderPos()
{
    return this->senderPos;
}

void RSUBeacon::setSenderPos(const Coord& senderPos)
{
    this->senderPos = senderPos;
}

Coord& RSUBeacon::getSenderSpeed()
{
    return this->senderSpeed;
}

void RSUBeacon::setSenderSpeed(const Coord& senderSpeed)
{
    this->senderSpeed = senderSpeed;
}

class RSUBeaconDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RSUBeaconDescriptor();
    virtual ~RSUBeaconDescriptor();

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

Register_ClassDescriptor(RSUBeaconDescriptor)

RSUBeaconDescriptor::RSUBeaconDescriptor() : omnetpp::cClassDescriptor("veins::RSUBeacon", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

RSUBeaconDescriptor::~RSUBeaconDescriptor()
{
    delete[] propertynames;
}

bool RSUBeaconDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RSUBeacon *>(obj)!=nullptr;
}

const char **RSUBeaconDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RSUBeaconDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RSUBeaconDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int RSUBeaconDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *RSUBeaconDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderMacAddr",
        "senderPos",
        "senderSpeed",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int RSUBeaconDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderMacAddr")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderPos")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderSpeed")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RSUBeaconDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "LAddress::L2Type",
        "Coord",
        "Coord",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **RSUBeaconDescriptor::getFieldPropertyNames(int field) const
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

const char *RSUBeaconDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int RSUBeaconDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RSUBeacon *pp = (RSUBeacon *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RSUBeaconDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RSUBeacon *pp = (RSUBeacon *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RSUBeaconDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RSUBeacon *pp = (RSUBeacon *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSenderMacAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getSenderPos(); return out.str();}
        case 2: {std::stringstream out; out << pp->getSenderSpeed(); return out.str();}
        default: return "";
    }
}

bool RSUBeaconDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RSUBeacon *pp = (RSUBeacon *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *RSUBeaconDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(LAddress::L2Type));
        case 1: return omnetpp::opp_typename(typeid(Coord));
        case 2: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *RSUBeaconDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RSUBeacon *pp = (RSUBeacon *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSenderMacAddr()); break;
        case 1: return (void *)(&pp->getSenderPos()); break;
        case 2: return (void *)(&pp->getSenderSpeed()); break;
        default: return nullptr;
    }
}

} // namespace veins


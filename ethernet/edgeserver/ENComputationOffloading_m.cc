//
// Generated file, do not edit! Created by nedtool 5.6 from inet/applications/ethernet/edgeserver/ENComputationOffloading.msg.
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
#include <memory>
#include "ENComputationOffloading_m.h"

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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

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

Register_Class(ENCOReq)

ENCOReq::ENCOReq() : ::inet::FieldsChunk()
{
}

ENCOReq::ENCOReq(const ENCOReq& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

ENCOReq::~ENCOReq()
{
}

ENCOReq& ENCOReq::operator=(const ENCOReq& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void ENCOReq::copy(const ENCOReq& other)
{
    this->taskID = other.taskID;
    this->constraint = other.constraint;
    this->requiredCycle = other.requiredCycle;
    this->taskCode = other.taskCode;
    this->CarAddr = other.CarAddr;
    this->reqTime = other.reqTime;
}

void ENCOReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->taskID);
    doParsimPacking(b,this->constraint);
    doParsimPacking(b,this->requiredCycle);
    doParsimPacking(b,this->taskCode);
    doParsimPacking(b,this->CarAddr);
    doParsimPacking(b,this->reqTime);
}

void ENCOReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->taskID);
    doParsimUnpacking(b,this->constraint);
    doParsimUnpacking(b,this->requiredCycle);
    doParsimUnpacking(b,this->taskCode);
    doParsimUnpacking(b,this->CarAddr);
    doParsimUnpacking(b,this->reqTime);
}

int ENCOReq::getTaskID() const
{
    return this->taskID;
}

void ENCOReq::setTaskID(int taskID)
{
    handleChange();
    this->taskID = taskID;
}

double ENCOReq::getConstraint() const
{
    return this->constraint;
}

void ENCOReq::setConstraint(double constraint)
{
    handleChange();
    this->constraint = constraint;
}

int ENCOReq::getRequiredCycle() const
{
    return this->requiredCycle;
}

void ENCOReq::setRequiredCycle(int requiredCycle)
{
    handleChange();
    this->requiredCycle = requiredCycle;
}

int ENCOReq::getTaskCode() const
{
    return this->taskCode;
}

void ENCOReq::setTaskCode(int taskCode)
{
    handleChange();
    this->taskCode = taskCode;
}

long ENCOReq::getCarAddr() const
{
    return this->CarAddr;
}

void ENCOReq::setCarAddr(long CarAddr)
{
    handleChange();
    this->CarAddr = CarAddr;
}

omnetpp::simtime_t ENCOReq::getReqTime() const
{
    return this->reqTime;
}

void ENCOReq::setReqTime(omnetpp::simtime_t reqTime)
{
    handleChange();
    this->reqTime = reqTime;
}

class ENCOReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_taskID,
        FIELD_constraint,
        FIELD_requiredCycle,
        FIELD_taskCode,
        FIELD_CarAddr,
        FIELD_reqTime,
    };
  public:
    ENCOReqDescriptor();
    virtual ~ENCOReqDescriptor();

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

Register_ClassDescriptor(ENCOReqDescriptor)

ENCOReqDescriptor::ENCOReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ENCOReq)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

ENCOReqDescriptor::~ENCOReqDescriptor()
{
    delete[] propertynames;
}

bool ENCOReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ENCOReq *>(obj)!=nullptr;
}

const char **ENCOReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ENCOReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ENCOReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int ENCOReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_taskID
        FD_ISEDITABLE,    // FIELD_constraint
        FD_ISEDITABLE,    // FIELD_requiredCycle
        FD_ISEDITABLE,    // FIELD_taskCode
        FD_ISEDITABLE,    // FIELD_CarAddr
        0,    // FIELD_reqTime
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *ENCOReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "taskID",
        "constraint",
        "requiredCycle",
        "taskCode",
        "CarAddr",
        "reqTime",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int ENCOReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 't' && strcmp(fieldName, "taskID") == 0) return base+0;
    if (fieldName[0] == 'c' && strcmp(fieldName, "constraint") == 0) return base+1;
    if (fieldName[0] == 'r' && strcmp(fieldName, "requiredCycle") == 0) return base+2;
    if (fieldName[0] == 't' && strcmp(fieldName, "taskCode") == 0) return base+3;
    if (fieldName[0] == 'C' && strcmp(fieldName, "CarAddr") == 0) return base+4;
    if (fieldName[0] == 'r' && strcmp(fieldName, "reqTime") == 0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ENCOReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_taskID
        "double",    // FIELD_constraint
        "int",    // FIELD_requiredCycle
        "int",    // FIELD_taskCode
        "long",    // FIELD_CarAddr
        "omnetpp::simtime_t",    // FIELD_reqTime
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **ENCOReqDescriptor::getFieldPropertyNames(int field) const
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

const char *ENCOReqDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ENCOReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ENCOReq *pp = (ENCOReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ENCOReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ENCOReq *pp = (ENCOReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ENCOReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ENCOReq *pp = (ENCOReq *)object; (void)pp;
    switch (field) {
        case FIELD_taskID: return long2string(pp->getTaskID());
        case FIELD_constraint: return double2string(pp->getConstraint());
        case FIELD_requiredCycle: return long2string(pp->getRequiredCycle());
        case FIELD_taskCode: return long2string(pp->getTaskCode());
        case FIELD_CarAddr: return long2string(pp->getCarAddr());
        case FIELD_reqTime: return simtime2string(pp->getReqTime());
        default: return "";
    }
}

bool ENCOReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ENCOReq *pp = (ENCOReq *)object; (void)pp;
    switch (field) {
        case FIELD_taskID: pp->setTaskID(string2long(value)); return true;
        case FIELD_constraint: pp->setConstraint(string2double(value)); return true;
        case FIELD_requiredCycle: pp->setRequiredCycle(string2long(value)); return true;
        case FIELD_taskCode: pp->setTaskCode(string2long(value)); return true;
        case FIELD_CarAddr: pp->setCarAddr(string2long(value)); return true;
        default: return false;
    }
}

const char *ENCOReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *ENCOReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ENCOReq *pp = (ENCOReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(ENCOResp)

ENCOResp::ENCOResp() : ::inet::FieldsChunk()
{
}

ENCOResp::ENCOResp(const ENCOResp& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

ENCOResp::~ENCOResp()
{
}

ENCOResp& ENCOResp::operator=(const ENCOResp& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void ENCOResp::copy(const ENCOResp& other)
{
    this->taskID = other.taskID;
    this->COResult = other.COResult;
    this->CarAddr = other.CarAddr;
}

void ENCOResp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->taskID);
    doParsimPacking(b,this->COResult);
    doParsimPacking(b,this->CarAddr);
}

void ENCOResp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->taskID);
    doParsimUnpacking(b,this->COResult);
    doParsimUnpacking(b,this->CarAddr);
}

int ENCOResp::getTaskID() const
{
    return this->taskID;
}

void ENCOResp::setTaskID(int taskID)
{
    handleChange();
    this->taskID = taskID;
}

int ENCOResp::getCOResult() const
{
    return this->COResult;
}

void ENCOResp::setCOResult(int COResult)
{
    handleChange();
    this->COResult = COResult;
}

long ENCOResp::getCarAddr() const
{
    return this->CarAddr;
}

void ENCOResp::setCarAddr(long CarAddr)
{
    handleChange();
    this->CarAddr = CarAddr;
}

class ENCORespDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_taskID,
        FIELD_COResult,
        FIELD_CarAddr,
    };
  public:
    ENCORespDescriptor();
    virtual ~ENCORespDescriptor();

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

Register_ClassDescriptor(ENCORespDescriptor)

ENCORespDescriptor::ENCORespDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ENCOResp)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

ENCORespDescriptor::~ENCORespDescriptor()
{
    delete[] propertynames;
}

bool ENCORespDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ENCOResp *>(obj)!=nullptr;
}

const char **ENCORespDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ENCORespDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ENCORespDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int ENCORespDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_taskID
        FD_ISEDITABLE,    // FIELD_COResult
        FD_ISEDITABLE,    // FIELD_CarAddr
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *ENCORespDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "taskID",
        "COResult",
        "CarAddr",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int ENCORespDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 't' && strcmp(fieldName, "taskID") == 0) return base+0;
    if (fieldName[0] == 'C' && strcmp(fieldName, "COResult") == 0) return base+1;
    if (fieldName[0] == 'C' && strcmp(fieldName, "CarAddr") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ENCORespDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_taskID
        "int",    // FIELD_COResult
        "long",    // FIELD_CarAddr
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **ENCORespDescriptor::getFieldPropertyNames(int field) const
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

const char *ENCORespDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ENCORespDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ENCOResp *pp = (ENCOResp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ENCORespDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ENCOResp *pp = (ENCOResp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ENCORespDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ENCOResp *pp = (ENCOResp *)object; (void)pp;
    switch (field) {
        case FIELD_taskID: return long2string(pp->getTaskID());
        case FIELD_COResult: return long2string(pp->getCOResult());
        case FIELD_CarAddr: return long2string(pp->getCarAddr());
        default: return "";
    }
}

bool ENCORespDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ENCOResp *pp = (ENCOResp *)object; (void)pp;
    switch (field) {
        case FIELD_taskID: pp->setTaskID(string2long(value)); return true;
        case FIELD_COResult: pp->setCOResult(string2long(value)); return true;
        case FIELD_CarAddr: pp->setCarAddr(string2long(value)); return true;
        default: return false;
    }
}

const char *ENCORespDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *ENCORespDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ENCOResp *pp = (ENCOResp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(OptimalESInfo)

OptimalESInfo::OptimalESInfo() : ::inet::FieldsChunk()
{
}

OptimalESInfo::OptimalESInfo(const OptimalESInfo& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

OptimalESInfo::~OptimalESInfo()
{
}

OptimalESInfo& OptimalESInfo::operator=(const OptimalESInfo& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void OptimalESInfo::copy(const OptimalESInfo& other)
{
    this->ESMacAddr = other.ESMacAddr;
    this->RSUMacAddr = other.RSUMacAddr;
    this->f = other.f;
}

void OptimalESInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->ESMacAddr);
    doParsimPacking(b,this->RSUMacAddr);
    doParsimPacking(b,this->f);
}

void OptimalESInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->ESMacAddr);
    doParsimUnpacking(b,this->RSUMacAddr);
    doParsimUnpacking(b,this->f);
}

const MacAddress& OptimalESInfo::getESMacAddr() const
{
    return this->ESMacAddr;
}

void OptimalESInfo::setESMacAddr(const MacAddress& ESMacAddr)
{
    handleChange();
    this->ESMacAddr = ESMacAddr;
}

const MacAddress& OptimalESInfo::getRSUMacAddr() const
{
    return this->RSUMacAddr;
}

void OptimalESInfo::setRSUMacAddr(const MacAddress& RSUMacAddr)
{
    handleChange();
    this->RSUMacAddr = RSUMacAddr;
}

int OptimalESInfo::getF() const
{
    return this->f;
}

void OptimalESInfo::setF(int f)
{
    handleChange();
    this->f = f;
}

class OptimalESInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_ESMacAddr,
        FIELD_RSUMacAddr,
        FIELD_f,
    };
  public:
    OptimalESInfoDescriptor();
    virtual ~OptimalESInfoDescriptor();

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

Register_ClassDescriptor(OptimalESInfoDescriptor)

OptimalESInfoDescriptor::OptimalESInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::OptimalESInfo)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

OptimalESInfoDescriptor::~OptimalESInfoDescriptor()
{
    delete[] propertynames;
}

bool OptimalESInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<OptimalESInfo *>(obj)!=nullptr;
}

const char **OptimalESInfoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *OptimalESInfoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int OptimalESInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int OptimalESInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_ESMacAddr
        0,    // FIELD_RSUMacAddr
        FD_ISEDITABLE,    // FIELD_f
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *OptimalESInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ESMacAddr",
        "RSUMacAddr",
        "f",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int OptimalESInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'E' && strcmp(fieldName, "ESMacAddr") == 0) return base+0;
    if (fieldName[0] == 'R' && strcmp(fieldName, "RSUMacAddr") == 0) return base+1;
    if (fieldName[0] == 'f' && strcmp(fieldName, "f") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *OptimalESInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_ESMacAddr
        "inet::MacAddress",    // FIELD_RSUMacAddr
        "int",    // FIELD_f
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **OptimalESInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *OptimalESInfoDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int OptimalESInfoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    OptimalESInfo *pp = (OptimalESInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *OptimalESInfoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    OptimalESInfo *pp = (OptimalESInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string OptimalESInfoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    OptimalESInfo *pp = (OptimalESInfo *)object; (void)pp;
    switch (field) {
        case FIELD_ESMacAddr: return pp->getESMacAddr().str();
        case FIELD_RSUMacAddr: return pp->getRSUMacAddr().str();
        case FIELD_f: return long2string(pp->getF());
        default: return "";
    }
}

bool OptimalESInfoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    OptimalESInfo *pp = (OptimalESInfo *)object; (void)pp;
    switch (field) {
        case FIELD_f: pp->setF(string2long(value)); return true;
        default: return false;
    }
}

const char *OptimalESInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *OptimalESInfoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    OptimalESInfo *pp = (OptimalESInfo *)object; (void)pp;
    switch (field) {
        case FIELD_ESMacAddr: return toVoidPtr(&pp->getESMacAddr()); break;
        case FIELD_RSUMacAddr: return toVoidPtr(&pp->getRSUMacAddr()); break;
        default: return nullptr;
    }
}

Register_Class(AvailabilityInfo)

AvailabilityInfo::AvailabilityInfo() : ::inet::FieldsChunk()
{
}

AvailabilityInfo::AvailabilityInfo(const AvailabilityInfo& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

AvailabilityInfo::~AvailabilityInfo()
{
}

AvailabilityInfo& AvailabilityInfo::operator=(const AvailabilityInfo& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void AvailabilityInfo::copy(const AvailabilityInfo& other)
{
    this->isAvailable_ = other.isAvailable_;
}

void AvailabilityInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->isAvailable_);
}

void AvailabilityInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->isAvailable_);
}

bool AvailabilityInfo::isAvailable() const
{
    return this->isAvailable_;
}

void AvailabilityInfo::setIsAvailable(bool isAvailable)
{
    handleChange();
    this->isAvailable_ = isAvailable;
}

class AvailabilityInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_isAvailable,
    };
  public:
    AvailabilityInfoDescriptor();
    virtual ~AvailabilityInfoDescriptor();

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

Register_ClassDescriptor(AvailabilityInfoDescriptor)

AvailabilityInfoDescriptor::AvailabilityInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::AvailabilityInfo)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

AvailabilityInfoDescriptor::~AvailabilityInfoDescriptor()
{
    delete[] propertynames;
}

bool AvailabilityInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AvailabilityInfo *>(obj)!=nullptr;
}

const char **AvailabilityInfoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *AvailabilityInfoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int AvailabilityInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int AvailabilityInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_isAvailable
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *AvailabilityInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "isAvailable",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int AvailabilityInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isAvailable") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *AvailabilityInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_isAvailable
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **AvailabilityInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *AvailabilityInfoDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int AvailabilityInfoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    AvailabilityInfo *pp = (AvailabilityInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *AvailabilityInfoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AvailabilityInfo *pp = (AvailabilityInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AvailabilityInfoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AvailabilityInfo *pp = (AvailabilityInfo *)object; (void)pp;
    switch (field) {
        case FIELD_isAvailable: return bool2string(pp->isAvailable());
        default: return "";
    }
}

bool AvailabilityInfoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    AvailabilityInfo *pp = (AvailabilityInfo *)object; (void)pp;
    switch (field) {
        case FIELD_isAvailable: pp->setIsAvailable(string2bool(value)); return true;
        default: return false;
    }
}

const char *AvailabilityInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *AvailabilityInfoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    AvailabilityInfo *pp = (AvailabilityInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace inet


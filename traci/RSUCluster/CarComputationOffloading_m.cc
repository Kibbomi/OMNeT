//
// Generated file, do not edit! Created by nedtool 5.6 from veins/modules/application/traci/RSUCluster/CarComputationOffloading.msg.
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
#include "CarComputationOffloading_m.h"

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

Register_Class(CarCOReq)

CarCOReq::CarCOReq(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->x = 0;
    this->y = 0;
    this->rad = 0;
    this->speed = 0;
    this->taskID = 0;
    this->constraint = 0;
    this->requiredCycle = 0;
    this->taskCode = 0;
    this->reqTime = 0;
}

CarCOReq::CarCOReq(const CarCOReq& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

CarCOReq::~CarCOReq()
{
}

CarCOReq& CarCOReq::operator=(const CarCOReq& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void CarCOReq::copy(const CarCOReq& other)
{
    this->x = other.x;
    this->y = other.y;
    this->rad = other.rad;
    this->speed = other.speed;
    this->carName = other.carName;
    this->CarAddr = other.CarAddr;
    this->taskID = other.taskID;
    this->constraint = other.constraint;
    this->requiredCycle = other.requiredCycle;
    this->taskCode = other.taskCode;
    this->reqTime = other.reqTime;
}

void CarCOReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->x);
    doParsimPacking(b,this->y);
    doParsimPacking(b,this->rad);
    doParsimPacking(b,this->speed);
    doParsimPacking(b,this->carName);
    doParsimPacking(b,this->CarAddr);
    doParsimPacking(b,this->taskID);
    doParsimPacking(b,this->constraint);
    doParsimPacking(b,this->requiredCycle);
    doParsimPacking(b,this->taskCode);
    doParsimPacking(b,this->reqTime);
}

void CarCOReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->x);
    doParsimUnpacking(b,this->y);
    doParsimUnpacking(b,this->rad);
    doParsimUnpacking(b,this->speed);
    doParsimUnpacking(b,this->carName);
    doParsimUnpacking(b,this->CarAddr);
    doParsimUnpacking(b,this->taskID);
    doParsimUnpacking(b,this->constraint);
    doParsimUnpacking(b,this->requiredCycle);
    doParsimUnpacking(b,this->taskCode);
    doParsimUnpacking(b,this->reqTime);
}

double CarCOReq::getX() const
{
    return this->x;
}

void CarCOReq::setX(double x)
{
    this->x = x;
}

double CarCOReq::getY() const
{
    return this->y;
}

void CarCOReq::setY(double y)
{
    this->y = y;
}

double CarCOReq::getRad() const
{
    return this->rad;
}

void CarCOReq::setRad(double rad)
{
    this->rad = rad;
}

double CarCOReq::getSpeed() const
{
    return this->speed;
}

void CarCOReq::setSpeed(double speed)
{
    this->speed = speed;
}

const char * CarCOReq::getCarName() const
{
    return this->carName.c_str();
}

void CarCOReq::setCarName(const char * carName)
{
    this->carName = carName;
}

LAddress::L2Type& CarCOReq::getCarAddr()
{
    return this->CarAddr;
}

void CarCOReq::setCarAddr(const LAddress::L2Type& CarAddr)
{
    this->CarAddr = CarAddr;
}

int CarCOReq::getTaskID() const
{
    return this->taskID;
}

void CarCOReq::setTaskID(int taskID)
{
    this->taskID = taskID;
}

double CarCOReq::getConstraint() const
{
    return this->constraint;
}

void CarCOReq::setConstraint(double constraint)
{
    this->constraint = constraint;
}

double CarCOReq::getRequiredCycle() const
{
    return this->requiredCycle;
}

void CarCOReq::setRequiredCycle(double requiredCycle)
{
    this->requiredCycle = requiredCycle;
}

double CarCOReq::getTaskCode() const
{
    return this->taskCode;
}

void CarCOReq::setTaskCode(double taskCode)
{
    this->taskCode = taskCode;
}

::omnetpp::simtime_t CarCOReq::getReqTime() const
{
    return this->reqTime;
}

void CarCOReq::setReqTime(::omnetpp::simtime_t reqTime)
{
    this->reqTime = reqTime;
}

class CarCOReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CarCOReqDescriptor();
    virtual ~CarCOReqDescriptor();

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

Register_ClassDescriptor(CarCOReqDescriptor)

CarCOReqDescriptor::CarCOReqDescriptor() : omnetpp::cClassDescriptor("veins::CarCOReq", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

CarCOReqDescriptor::~CarCOReqDescriptor()
{
    delete[] propertynames;
}

bool CarCOReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CarCOReq *>(obj)!=nullptr;
}

const char **CarCOReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CarCOReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CarCOReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount() : 11;
}

unsigned int CarCOReqDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *CarCOReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "x",
        "y",
        "rad",
        "speed",
        "carName",
        "CarAddr",
        "taskID",
        "constraint",
        "requiredCycle",
        "taskCode",
        "reqTime",
    };
    return (field>=0 && field<11) ? fieldNames[field] : nullptr;
}

int CarCOReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+0;
    if (fieldName[0]=='y' && strcmp(fieldName, "y")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "rad")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "speed")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "carName")==0) return base+4;
    if (fieldName[0]=='C' && strcmp(fieldName, "CarAddr")==0) return base+5;
    if (fieldName[0]=='t' && strcmp(fieldName, "taskID")==0) return base+6;
    if (fieldName[0]=='c' && strcmp(fieldName, "constraint")==0) return base+7;
    if (fieldName[0]=='r' && strcmp(fieldName, "requiredCycle")==0) return base+8;
    if (fieldName[0]=='t' && strcmp(fieldName, "taskCode")==0) return base+9;
    if (fieldName[0]=='r' && strcmp(fieldName, "reqTime")==0) return base+10;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CarCOReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "double",
        "double",
        "double",
        "string",
        "LAddress::L2Type",
        "int",
        "double",
        "double",
        "double",
        "simtime_t",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : nullptr;
}

const char **CarCOReqDescriptor::getFieldPropertyNames(int field) const
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

const char *CarCOReqDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CarCOReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CarCOReq *pp = (CarCOReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CarCOReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CarCOReq *pp = (CarCOReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CarCOReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CarCOReq *pp = (CarCOReq *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getX());
        case 1: return double2string(pp->getY());
        case 2: return double2string(pp->getRad());
        case 3: return double2string(pp->getSpeed());
        case 4: return oppstring2string(pp->getCarName());
        case 5: {std::stringstream out; out << pp->getCarAddr(); return out.str();}
        case 6: return long2string(pp->getTaskID());
        case 7: return double2string(pp->getConstraint());
        case 8: return double2string(pp->getRequiredCycle());
        case 9: return double2string(pp->getTaskCode());
        case 10: return simtime2string(pp->getReqTime());
        default: return "";
    }
}

bool CarCOReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CarCOReq *pp = (CarCOReq *)object; (void)pp;
    switch (field) {
        case 0: pp->setX(string2double(value)); return true;
        case 1: pp->setY(string2double(value)); return true;
        case 2: pp->setRad(string2double(value)); return true;
        case 3: pp->setSpeed(string2double(value)); return true;
        case 4: pp->setCarName((value)); return true;
        case 6: pp->setTaskID(string2long(value)); return true;
        case 7: pp->setConstraint(string2double(value)); return true;
        case 8: pp->setRequiredCycle(string2double(value)); return true;
        case 9: pp->setTaskCode(string2double(value)); return true;
        case 10: pp->setReqTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *CarCOReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 5: return omnetpp::opp_typename(typeid(LAddress::L2Type));
        default: return nullptr;
    };
}

void *CarCOReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CarCOReq *pp = (CarCOReq *)object; (void)pp;
    switch (field) {
        case 5: return (void *)(&pp->getCarAddr()); break;
        default: return nullptr;
    }
}

Register_Class(CarCOResp)

CarCOResp::CarCOResp(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->taskID = 0;
    this->COResult = 0;
}

CarCOResp::CarCOResp(const CarCOResp& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

CarCOResp::~CarCOResp()
{
}

CarCOResp& CarCOResp::operator=(const CarCOResp& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void CarCOResp::copy(const CarCOResp& other)
{
    this->taskID = other.taskID;
    this->COResult = other.COResult;
}

void CarCOResp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->taskID);
    doParsimPacking(b,this->COResult);
}

void CarCOResp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->taskID);
    doParsimUnpacking(b,this->COResult);
}

int CarCOResp::getTaskID() const
{
    return this->taskID;
}

void CarCOResp::setTaskID(int taskID)
{
    this->taskID = taskID;
}

int CarCOResp::getCOResult() const
{
    return this->COResult;
}

void CarCOResp::setCOResult(int COResult)
{
    this->COResult = COResult;
}

class CarCORespDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CarCORespDescriptor();
    virtual ~CarCORespDescriptor();

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

Register_ClassDescriptor(CarCORespDescriptor)

CarCORespDescriptor::CarCORespDescriptor() : omnetpp::cClassDescriptor("veins::CarCOResp", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

CarCORespDescriptor::~CarCORespDescriptor()
{
    delete[] propertynames;
}

bool CarCORespDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CarCOResp *>(obj)!=nullptr;
}

const char **CarCORespDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CarCORespDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CarCORespDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int CarCORespDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *CarCORespDescriptor::getFieldName(int field) const
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
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int CarCORespDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "taskID")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "COResult")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CarCORespDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **CarCORespDescriptor::getFieldPropertyNames(int field) const
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

const char *CarCORespDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CarCORespDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CarCOResp *pp = (CarCOResp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CarCORespDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CarCOResp *pp = (CarCOResp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CarCORespDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CarCOResp *pp = (CarCOResp *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getTaskID());
        case 1: return long2string(pp->getCOResult());
        default: return "";
    }
}

bool CarCORespDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CarCOResp *pp = (CarCOResp *)object; (void)pp;
    switch (field) {
        case 0: pp->setTaskID(string2long(value)); return true;
        case 1: pp->setCOResult(string2long(value)); return true;
        default: return false;
    }
}

const char *CarCORespDescriptor::getFieldStructName(int field) const
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

void *CarCORespDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CarCOResp *pp = (CarCOResp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(RSUCOLevel)

RSUCOLevel::RSUCOLevel(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->COLevel = false;
}

RSUCOLevel::RSUCOLevel(const RSUCOLevel& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

RSUCOLevel::~RSUCOLevel()
{
}

RSUCOLevel& RSUCOLevel::operator=(const RSUCOLevel& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void RSUCOLevel::copy(const RSUCOLevel& other)
{
    this->RSUAddr = other.RSUAddr;
    this->COLevel = other.COLevel;
}

void RSUCOLevel::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->RSUAddr);
    doParsimPacking(b,this->COLevel);
}

void RSUCOLevel::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->RSUAddr);
    doParsimUnpacking(b,this->COLevel);
}

LAddress::L2Type& RSUCOLevel::getRSUAddr()
{
    return this->RSUAddr;
}

void RSUCOLevel::setRSUAddr(const LAddress::L2Type& RSUAddr)
{
    this->RSUAddr = RSUAddr;
}

bool RSUCOLevel::getCOLevel() const
{
    return this->COLevel;
}

void RSUCOLevel::setCOLevel(bool COLevel)
{
    this->COLevel = COLevel;
}

class RSUCOLevelDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RSUCOLevelDescriptor();
    virtual ~RSUCOLevelDescriptor();

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

Register_ClassDescriptor(RSUCOLevelDescriptor)

RSUCOLevelDescriptor::RSUCOLevelDescriptor() : omnetpp::cClassDescriptor("veins::RSUCOLevel", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

RSUCOLevelDescriptor::~RSUCOLevelDescriptor()
{
    delete[] propertynames;
}

bool RSUCOLevelDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RSUCOLevel *>(obj)!=nullptr;
}

const char **RSUCOLevelDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RSUCOLevelDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RSUCOLevelDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int RSUCOLevelDescriptor::getFieldTypeFlags(int field) const
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

const char *RSUCOLevelDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "RSUAddr",
        "COLevel",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int RSUCOLevelDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RSUAddr")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "COLevel")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RSUCOLevelDescriptor::getFieldTypeString(int field) const
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

const char **RSUCOLevelDescriptor::getFieldPropertyNames(int field) const
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

const char *RSUCOLevelDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int RSUCOLevelDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RSUCOLevel *pp = (RSUCOLevel *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *RSUCOLevelDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RSUCOLevel *pp = (RSUCOLevel *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RSUCOLevelDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RSUCOLevel *pp = (RSUCOLevel *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRSUAddr(); return out.str();}
        case 1: return bool2string(pp->getCOLevel());
        default: return "";
    }
}

bool RSUCOLevelDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RSUCOLevel *pp = (RSUCOLevel *)object; (void)pp;
    switch (field) {
        case 1: pp->setCOLevel(string2bool(value)); return true;
        default: return false;
    }
}

const char *RSUCOLevelDescriptor::getFieldStructName(int field) const
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

void *RSUCOLevelDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RSUCOLevel *pp = (RSUCOLevel *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRSUAddr()); break;
        default: return nullptr;
    }
}

Register_Class(CarCOAck)

CarCOAck::CarCOAck(const char *name, short kind) : ::veins::BaseFrame1609_4(name,kind)
{
    this->taskID = 0;
    this->CarAddr = 0;
}

CarCOAck::CarCOAck(const CarCOAck& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

CarCOAck::~CarCOAck()
{
}

CarCOAck& CarCOAck::operator=(const CarCOAck& other)
{
    if (this==&other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void CarCOAck::copy(const CarCOAck& other)
{
    this->taskID = other.taskID;
    this->CarAddr = other.CarAddr;
}

void CarCOAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->taskID);
    doParsimPacking(b,this->CarAddr);
}

void CarCOAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->taskID);
    doParsimUnpacking(b,this->CarAddr);
}

int CarCOAck::getTaskID() const
{
    return this->taskID;
}

void CarCOAck::setTaskID(int taskID)
{
    this->taskID = taskID;
}

long CarCOAck::getCarAddr() const
{
    return this->CarAddr;
}

void CarCOAck::setCarAddr(long CarAddr)
{
    this->CarAddr = CarAddr;
}

class CarCOAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CarCOAckDescriptor();
    virtual ~CarCOAckDescriptor();

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

Register_ClassDescriptor(CarCOAckDescriptor)

CarCOAckDescriptor::CarCOAckDescriptor() : omnetpp::cClassDescriptor("veins::CarCOAck", "veins::BaseFrame1609_4")
{
    propertynames = nullptr;
}

CarCOAckDescriptor::~CarCOAckDescriptor()
{
    delete[] propertynames;
}

bool CarCOAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CarCOAck *>(obj)!=nullptr;
}

const char **CarCOAckDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CarCOAckDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CarCOAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int CarCOAckDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *CarCOAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "taskID",
        "CarAddr",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int CarCOAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "taskID")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CarAddr")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CarCOAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "long",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **CarCOAckDescriptor::getFieldPropertyNames(int field) const
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

const char *CarCOAckDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CarCOAckDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CarCOAck *pp = (CarCOAck *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CarCOAckDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CarCOAck *pp = (CarCOAck *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CarCOAckDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CarCOAck *pp = (CarCOAck *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getTaskID());
        case 1: return long2string(pp->getCarAddr());
        default: return "";
    }
}

bool CarCOAckDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CarCOAck *pp = (CarCOAck *)object; (void)pp;
    switch (field) {
        case 0: pp->setTaskID(string2long(value)); return true;
        case 1: pp->setCarAddr(string2long(value)); return true;
        default: return false;
    }
}

const char *CarCOAckDescriptor::getFieldStructName(int field) const
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

void *CarCOAckDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CarCOAck *pp = (CarCOAck *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace veins


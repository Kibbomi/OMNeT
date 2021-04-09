//
// Generated file, do not edit! Created by nedtool 5.6 from inet/applications/ethernet/MyEthernetExample/MyEtherMsg.msg.
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
#include "MyEtherMsg_m.h"

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

Register_Class(MyEtherAppReq)

MyEtherAppReq::MyEtherAppReq() : ::inet::FieldsChunk()
{
}

MyEtherAppReq::MyEtherAppReq(const MyEtherAppReq& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

MyEtherAppReq::~MyEtherAppReq()
{
}

MyEtherAppReq& MyEtherAppReq::operator=(const MyEtherAppReq& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void MyEtherAppReq::copy(const MyEtherAppReq& other)
{
    this->requestId = other.requestId;
    this->responseBytes = other.responseBytes;
    this->hello = other.hello;
}

void MyEtherAppReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->requestId);
    doParsimPacking(b,this->responseBytes);
    doParsimPacking(b,this->hello);
}

void MyEtherAppReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->requestId);
    doParsimUnpacking(b,this->responseBytes);
    doParsimUnpacking(b,this->hello);
}

long MyEtherAppReq::getRequestId() const
{
    return this->requestId;
}

void MyEtherAppReq::setRequestId(long requestId)
{
    handleChange();
    this->requestId = requestId;
}

long MyEtherAppReq::getResponseBytes() const
{
    return this->responseBytes;
}

void MyEtherAppReq::setResponseBytes(long responseBytes)
{
    handleChange();
    this->responseBytes = responseBytes;
}

int MyEtherAppReq::getHello() const
{
    return this->hello;
}

void MyEtherAppReq::setHello(int hello)
{
    handleChange();
    this->hello = hello;
}

class MyEtherAppReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_requestId,
        FIELD_responseBytes,
        FIELD_hello,
    };
  public:
    MyEtherAppReqDescriptor();
    virtual ~MyEtherAppReqDescriptor();

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

Register_ClassDescriptor(MyEtherAppReqDescriptor)

MyEtherAppReqDescriptor::MyEtherAppReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::MyEtherAppReq)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

MyEtherAppReqDescriptor::~MyEtherAppReqDescriptor()
{
    delete[] propertynames;
}

bool MyEtherAppReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MyEtherAppReq *>(obj)!=nullptr;
}

const char **MyEtherAppReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MyEtherAppReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MyEtherAppReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int MyEtherAppReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_requestId
        FD_ISEDITABLE,    // FIELD_responseBytes
        FD_ISEDITABLE,    // FIELD_hello
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *MyEtherAppReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requestId",
        "responseBytes",
        "hello",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int MyEtherAppReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "requestId") == 0) return base+0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "responseBytes") == 0) return base+1;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hello") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MyEtherAppReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "long",    // FIELD_requestId
        "long",    // FIELD_responseBytes
        "int",    // FIELD_hello
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **MyEtherAppReqDescriptor::getFieldPropertyNames(int field) const
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

const char *MyEtherAppReqDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int MyEtherAppReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppReq *pp = (MyEtherAppReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *MyEtherAppReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppReq *pp = (MyEtherAppReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MyEtherAppReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppReq *pp = (MyEtherAppReq *)object; (void)pp;
    switch (field) {
        case FIELD_requestId: return long2string(pp->getRequestId());
        case FIELD_responseBytes: return long2string(pp->getResponseBytes());
        case FIELD_hello: return long2string(pp->getHello());
        default: return "";
    }
}

bool MyEtherAppReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppReq *pp = (MyEtherAppReq *)object; (void)pp;
    switch (field) {
        case FIELD_requestId: pp->setRequestId(string2long(value)); return true;
        case FIELD_responseBytes: pp->setResponseBytes(string2long(value)); return true;
        case FIELD_hello: pp->setHello(string2long(value)); return true;
        default: return false;
    }
}

const char *MyEtherAppReqDescriptor::getFieldStructName(int field) const
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

void *MyEtherAppReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppReq *pp = (MyEtherAppReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(MyEtherAppResp)

MyEtherAppResp::MyEtherAppResp() : ::inet::FieldsChunk()
{
}

MyEtherAppResp::MyEtherAppResp(const MyEtherAppResp& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

MyEtherAppResp::~MyEtherAppResp()
{
}

MyEtherAppResp& MyEtherAppResp::operator=(const MyEtherAppResp& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void MyEtherAppResp::copy(const MyEtherAppResp& other)
{
    this->requestId = other.requestId;
    this->numFrames = other.numFrames;
    this->hello = other.hello;
}

void MyEtherAppResp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->requestId);
    doParsimPacking(b,this->numFrames);
    doParsimPacking(b,this->hello);
}

void MyEtherAppResp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->requestId);
    doParsimUnpacking(b,this->numFrames);
    doParsimUnpacking(b,this->hello);
}

int MyEtherAppResp::getRequestId() const
{
    return this->requestId;
}

void MyEtherAppResp::setRequestId(int requestId)
{
    handleChange();
    this->requestId = requestId;
}

int MyEtherAppResp::getNumFrames() const
{
    return this->numFrames;
}

void MyEtherAppResp::setNumFrames(int numFrames)
{
    handleChange();
    this->numFrames = numFrames;
}

int MyEtherAppResp::getHello() const
{
    return this->hello;
}

void MyEtherAppResp::setHello(int hello)
{
    handleChange();
    this->hello = hello;
}

class MyEtherAppRespDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_requestId,
        FIELD_numFrames,
        FIELD_hello,
    };
  public:
    MyEtherAppRespDescriptor();
    virtual ~MyEtherAppRespDescriptor();

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

Register_ClassDescriptor(MyEtherAppRespDescriptor)

MyEtherAppRespDescriptor::MyEtherAppRespDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::MyEtherAppResp)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

MyEtherAppRespDescriptor::~MyEtherAppRespDescriptor()
{
    delete[] propertynames;
}

bool MyEtherAppRespDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MyEtherAppResp *>(obj)!=nullptr;
}

const char **MyEtherAppRespDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MyEtherAppRespDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MyEtherAppRespDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int MyEtherAppRespDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_requestId
        FD_ISEDITABLE,    // FIELD_numFrames
        FD_ISEDITABLE,    // FIELD_hello
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *MyEtherAppRespDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requestId",
        "numFrames",
        "hello",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int MyEtherAppRespDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "requestId") == 0) return base+0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numFrames") == 0) return base+1;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hello") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MyEtherAppRespDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_requestId
        "int",    // FIELD_numFrames
        "int",    // FIELD_hello
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **MyEtherAppRespDescriptor::getFieldPropertyNames(int field) const
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

const char *MyEtherAppRespDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int MyEtherAppRespDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppResp *pp = (MyEtherAppResp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *MyEtherAppRespDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppResp *pp = (MyEtherAppResp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MyEtherAppRespDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppResp *pp = (MyEtherAppResp *)object; (void)pp;
    switch (field) {
        case FIELD_requestId: return long2string(pp->getRequestId());
        case FIELD_numFrames: return long2string(pp->getNumFrames());
        case FIELD_hello: return long2string(pp->getHello());
        default: return "";
    }
}

bool MyEtherAppRespDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppResp *pp = (MyEtherAppResp *)object; (void)pp;
    switch (field) {
        case FIELD_requestId: pp->setRequestId(string2long(value)); return true;
        case FIELD_numFrames: pp->setNumFrames(string2long(value)); return true;
        case FIELD_hello: pp->setHello(string2long(value)); return true;
        default: return false;
    }
}

const char *MyEtherAppRespDescriptor::getFieldStructName(int field) const
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

void *MyEtherAppRespDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    MyEtherAppResp *pp = (MyEtherAppResp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace inet


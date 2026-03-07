//
// Generated file, do not edit! Created by opp_msgtool 6.1 from DNP3Packet.msg.
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
#include <type_traits>
#include "DNP3Packet_m.h"

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

Register_Class(Dnp3Packet)

Dnp3Packet::Dnp3Packet(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

Dnp3Packet::Dnp3Packet(const Dnp3Packet& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Dnp3Packet::~Dnp3Packet()
{
}

Dnp3Packet& Dnp3Packet::operator=(const Dnp3Packet& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Dnp3Packet::copy(const Dnp3Packet& other)
{
    this->meterId = other.meterId;
    this->seq = other.seq;
    this->msgType = other.msgType;
    this->burst = other.burst;
}

void Dnp3Packet::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->meterId);
    doParsimPacking(b,this->seq);
    doParsimPacking(b,this->msgType);
    doParsimPacking(b,this->burst);
}

void Dnp3Packet::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->meterId);
    doParsimUnpacking(b,this->seq);
    doParsimUnpacking(b,this->msgType);
    doParsimUnpacking(b,this->burst);
}

int Dnp3Packet::getMeterId() const
{
    return this->meterId;
}

void Dnp3Packet::setMeterId(int meterId)
{
    this->meterId = meterId;
}

int Dnp3Packet::getSeq() const
{
    return this->seq;
}

void Dnp3Packet::setSeq(int seq)
{
    this->seq = seq;
}

const char * Dnp3Packet::getMsgType() const
{
    return this->msgType.c_str();
}

void Dnp3Packet::setMsgType(const char * msgType)
{
    this->msgType = msgType;
}

bool Dnp3Packet::getBurst() const
{
    return this->burst;
}

void Dnp3Packet::setBurst(bool burst)
{
    this->burst = burst;
}

class Dnp3PacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_meterId,
        FIELD_seq,
        FIELD_msgType,
        FIELD_burst,
    };
  public:
    Dnp3PacketDescriptor();
    virtual ~Dnp3PacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(Dnp3PacketDescriptor)

Dnp3PacketDescriptor::Dnp3PacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(Dnp3Packet)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

Dnp3PacketDescriptor::~Dnp3PacketDescriptor()
{
    delete[] propertyNames;
}

bool Dnp3PacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Dnp3Packet *>(obj)!=nullptr;
}

const char **Dnp3PacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Dnp3PacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Dnp3PacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Dnp3PacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_meterId
        FD_ISEDITABLE,    // FIELD_seq
        FD_ISEDITABLE,    // FIELD_msgType
        FD_ISEDITABLE,    // FIELD_burst
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Dnp3PacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "meterId",
        "seq",
        "msgType",
        "burst",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Dnp3PacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "meterId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "seq") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "msgType") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "burst") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Dnp3PacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_meterId
        "int",    // FIELD_seq
        "string",    // FIELD_msgType
        "bool",    // FIELD_burst
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Dnp3PacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Dnp3PacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Dnp3PacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Dnp3Packet *pp = omnetpp::fromAnyPtr<Dnp3Packet>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Dnp3PacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Dnp3Packet *pp = omnetpp::fromAnyPtr<Dnp3Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Dnp3Packet'", field);
    }
}

const char *Dnp3PacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Dnp3Packet *pp = omnetpp::fromAnyPtr<Dnp3Packet>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Dnp3PacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Dnp3Packet *pp = omnetpp::fromAnyPtr<Dnp3Packet>(object); (void)pp;
    switch (field) {
        case FIELD_meterId: return long2string(pp->getMeterId());
        case FIELD_seq: return long2string(pp->getSeq());
        case FIELD_msgType: return oppstring2string(pp->getMsgType());
        case FIELD_burst: return bool2string(pp->getBurst());
        default: return "";
    }
}

void Dnp3PacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Dnp3Packet *pp = omnetpp::fromAnyPtr<Dnp3Packet>(object); (void)pp;
    switch (field) {
        case FIELD_meterId: pp->setMeterId(string2long(value)); break;
        case FIELD_seq: pp->setSeq(string2long(value)); break;
        case FIELD_msgType: pp->setMsgType((value)); break;
        case FIELD_burst: pp->setBurst(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Dnp3Packet'", field);
    }
}

omnetpp::cValue Dnp3PacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Dnp3Packet *pp = omnetpp::fromAnyPtr<Dnp3Packet>(object); (void)pp;
    switch (field) {
        case FIELD_meterId: return pp->getMeterId();
        case FIELD_seq: return pp->getSeq();
        case FIELD_msgType: return pp->getMsgType();
        case FIELD_burst: return pp->getBurst();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Dnp3Packet' as cValue -- field index out of range?", field);
    }
}

void Dnp3PacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Dnp3Packet *pp = omnetpp::fromAnyPtr<Dnp3Packet>(object); (void)pp;
    switch (field) {
        case FIELD_meterId: pp->setMeterId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_seq: pp->setSeq(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_msgType: pp->setMsgType(value.stringValue()); break;
        case FIELD_burst: pp->setBurst(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Dnp3Packet'", field);
    }
}

const char *Dnp3PacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr Dnp3PacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Dnp3Packet *pp = omnetpp::fromAnyPtr<Dnp3Packet>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Dnp3PacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Dnp3Packet *pp = omnetpp::fromAnyPtr<Dnp3Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Dnp3Packet'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp


//
// Generated file, do not edit! Created by nedtool 5.6 from inet/applications/ethernet/edgeserver/ENComputationOffloading.msg.
//

#ifndef __INET_ENCOMPUTATIONOFFLOADING_M_H
#define __INET_ENCOMPUTATIONOFFLOADING_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

class ENCOReq;
class ENCOResp;
class OptimalESInfo;
class AvailabilityInfo;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress


namespace inet {

/**
 * Class generated from <tt>inet/applications/ethernet/edgeserver/ENComputationOffloading.msg:24</tt> by nedtool.
 * <pre>
 * class ENCOReq extends FieldsChunk
 * {
 *     //Task Information
 *     int taskID;
 *     double constraint;
 *     int requiredCycle;
 *     int taskCode;	//필요 없을 것 같음.Code는..	이미 시간에 반영..
 * 
 *     long CarAddr;	//MacAddress임.
 *     MacAddress toSendRSU;
 *     simtime_t reqTime;
 * }
 * </pre>
 */
class INET_API ENCOReq : public ::inet::FieldsChunk
{
  protected:
    int taskID = 0;
    double constraint = 0;
    int requiredCycle = 0;
    int taskCode = 0;
    long CarAddr = 0;
    MacAddress toSendRSU;
    omnetpp::simtime_t reqTime = SIMTIME_ZERO;

  private:
    void copy(const ENCOReq& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ENCOReq&);

  public:
    ENCOReq();
    ENCOReq(const ENCOReq& other);
    virtual ~ENCOReq();
    ENCOReq& operator=(const ENCOReq& other);
    virtual ENCOReq *dup() const override {return new ENCOReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getTaskID() const;
    virtual void setTaskID(int taskID);
    virtual double getConstraint() const;
    virtual void setConstraint(double constraint);
    virtual int getRequiredCycle() const;
    virtual void setRequiredCycle(int requiredCycle);
    virtual int getTaskCode() const;
    virtual void setTaskCode(int taskCode);
    virtual long getCarAddr() const;
    virtual void setCarAddr(long CarAddr);
    virtual const MacAddress& getToSendRSU() const;
    virtual MacAddress& getToSendRSUForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<ENCOReq*>(this)->getToSendRSU());}
    virtual void setToSendRSU(const MacAddress& toSendRSU);
    virtual omnetpp::simtime_t getReqTime() const;
    virtual void setReqTime(omnetpp::simtime_t reqTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ENCOReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ENCOReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/applications/ethernet/edgeserver/ENComputationOffloading.msg:37</tt> by nedtool.
 * <pre>
 * class ENCOResp extends FieldsChunk
 * {
 *     int taskID;
 *     int COResult;
 *     long CarAddr;
 * }
 * </pre>
 */
class INET_API ENCOResp : public ::inet::FieldsChunk
{
  protected:
    int taskID = 0;
    int COResult = 0;
    long CarAddr = 0;

  private:
    void copy(const ENCOResp& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ENCOResp&);

  public:
    ENCOResp();
    ENCOResp(const ENCOResp& other);
    virtual ~ENCOResp();
    ENCOResp& operator=(const ENCOResp& other);
    virtual ENCOResp *dup() const override {return new ENCOResp(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getTaskID() const;
    virtual void setTaskID(int taskID);
    virtual int getCOResult() const;
    virtual void setCOResult(int COResult);
    virtual long getCarAddr() const;
    virtual void setCarAddr(long CarAddr);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ENCOResp& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ENCOResp& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/applications/ethernet/edgeserver/ENComputationOffloading.msg:44</tt> by nedtool.
 * <pre>
 * class OptimalESInfo extends FieldsChunk
 * {
 *     MacAddress ESMacAddr;
 *     MacAddress RSUMacAddr;
 *     int f;
 *     bool isAvailable;	//f 가 0이면 false 아니면 true로 간접적으로 표현 가능할 듯.
 * }
 * </pre>
 */
class INET_API OptimalESInfo : public ::inet::FieldsChunk
{
  protected:
    MacAddress ESMacAddr;
    MacAddress RSUMacAddr;
    int f = 0;
    bool isAvailable_ = false;

  private:
    void copy(const OptimalESInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OptimalESInfo&);

  public:
    OptimalESInfo();
    OptimalESInfo(const OptimalESInfo& other);
    virtual ~OptimalESInfo();
    OptimalESInfo& operator=(const OptimalESInfo& other);
    virtual OptimalESInfo *dup() const override {return new OptimalESInfo(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const MacAddress& getESMacAddr() const;
    virtual MacAddress& getESMacAddrForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<OptimalESInfo*>(this)->getESMacAddr());}
    virtual void setESMacAddr(const MacAddress& ESMacAddr);
    virtual const MacAddress& getRSUMacAddr() const;
    virtual MacAddress& getRSUMacAddrForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<OptimalESInfo*>(this)->getRSUMacAddr());}
    virtual void setRSUMacAddr(const MacAddress& RSUMacAddr);
    virtual int getF() const;
    virtual void setF(int f);
    virtual bool isAvailable() const;
    virtual void setIsAvailable(bool isAvailable);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const OptimalESInfo& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, OptimalESInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/applications/ethernet/edgeserver/ENComputationOffloading.msg:52</tt> by nedtool.
 * <pre>
 * class AvailabilityInfo extends FieldsChunk
 * {
 *     //Mac주소는 송신자 Tag에서 구할 수 있음..
 *     bool isAvailable;
 * }
 * </pre>
 */
class INET_API AvailabilityInfo : public ::inet::FieldsChunk
{
  protected:
    bool isAvailable_ = false;

  private:
    void copy(const AvailabilityInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AvailabilityInfo&);

  public:
    AvailabilityInfo();
    AvailabilityInfo(const AvailabilityInfo& other);
    virtual ~AvailabilityInfo();
    AvailabilityInfo& operator=(const AvailabilityInfo& other);
    virtual AvailabilityInfo *dup() const override {return new AvailabilityInfo(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual bool isAvailable() const;
    virtual void setIsAvailable(bool isAvailable);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AvailabilityInfo& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AvailabilityInfo& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_ENCOMPUTATIONOFFLOADING_M_H


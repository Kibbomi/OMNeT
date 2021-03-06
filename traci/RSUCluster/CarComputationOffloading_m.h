//
// Generated file, do not edit! Created by nedtool 5.6 from veins/modules/application/traci/RSUCluster/CarComputationOffloading.msg.
//

#ifndef __VEINS_CARCOMPUTATIONOFFLOADING_M_H
#define __VEINS_CARCOMPUTATIONOFFLOADING_M_H

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
#ifndef VEINS_API
#  if defined(VEINS_EXPORT)
#    define VEINS_API  OPP_DLLEXPORT
#  elif defined(VEINS_IMPORT)
#    define VEINS_API  OPP_DLLIMPORT
#  else
#    define VEINS_API
#  endif
#endif

// cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/utility/Consts80211p.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"
// }}


namespace veins {

/**
 * Class generated from <tt>veins/modules/application/traci/RSUCluster/CarComputationOffloading.msg:32</tt> by nedtool.
 * <pre>
 * packet CarCOReq extends BaseFrame1609_4
 * {
 *     //Car information
 *     double x;
 *     double y;
 *     double rad;	//direction
 *     double speed;
 *     string carName;
 *     LAddress::L2Type CarAddr;
 * 
 *     //Task information
 *     int taskID;
 *     double constraint;		//unit s
 *     double requiredCycle;	//unit Gb
 *     double taskCode;		//unit Kb
 * 
 *     //Packet information
 *     simtime_t reqTime;
 * 
 * }
 * </pre>
 */
class VEINS_API CarCOReq : public ::veins::BaseFrame1609_4
{
  protected:
    double x;
    double y;
    double rad;
    double speed;
    ::omnetpp::opp_string carName;
    LAddress::L2Type CarAddr;
    int taskID;
    double constraint;
    double requiredCycle;
    double taskCode;
    ::omnetpp::simtime_t reqTime;

  private:
    void copy(const CarCOReq& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CarCOReq&);

  public:
    CarCOReq(const char *name=nullptr, short kind=0);
    CarCOReq(const CarCOReq& other);
    virtual ~CarCOReq();
    CarCOReq& operator=(const CarCOReq& other);
    virtual CarCOReq *dup() const override {return new CarCOReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getX() const;
    virtual void setX(double x);
    virtual double getY() const;
    virtual void setY(double y);
    virtual double getRad() const;
    virtual void setRad(double rad);
    virtual double getSpeed() const;
    virtual void setSpeed(double speed);
    virtual const char * getCarName() const;
    virtual void setCarName(const char * carName);
    virtual LAddress::L2Type& getCarAddr();
    virtual const LAddress::L2Type& getCarAddr() const {return const_cast<CarCOReq*>(this)->getCarAddr();}
    virtual void setCarAddr(const LAddress::L2Type& CarAddr);
    virtual int getTaskID() const;
    virtual void setTaskID(int taskID);
    virtual double getConstraint() const;
    virtual void setConstraint(double constraint);
    virtual double getRequiredCycle() const;
    virtual void setRequiredCycle(double requiredCycle);
    virtual double getTaskCode() const;
    virtual void setTaskCode(double taskCode);
    virtual ::omnetpp::simtime_t getReqTime() const;
    virtual void setReqTime(::omnetpp::simtime_t reqTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CarCOReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CarCOReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>veins/modules/application/traci/RSUCluster/CarComputationOffloading.msg:53</tt> by nedtool.
 * <pre>
 * packet CarCOResp extends BaseFrame1609_4
 * {
 *     int taskID;
 *     int COResult;
 * }
 * </pre>
 */
class VEINS_API CarCOResp : public ::veins::BaseFrame1609_4
{
  protected:
    int taskID;
    int COResult;

  private:
    void copy(const CarCOResp& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CarCOResp&);

  public:
    CarCOResp(const char *name=nullptr, short kind=0);
    CarCOResp(const CarCOResp& other);
    virtual ~CarCOResp();
    CarCOResp& operator=(const CarCOResp& other);
    virtual CarCOResp *dup() const override {return new CarCOResp(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getTaskID() const;
    virtual void setTaskID(int taskID);
    virtual int getCOResult() const;
    virtual void setCOResult(int COResult);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CarCOResp& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CarCOResp& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>veins/modules/application/traci/RSUCluster/CarComputationOffloading.msg:59</tt> by nedtool.
 * <pre>
 * packet RSUCOLevel extends BaseFrame1609_4
 * {
 *     LAddress::L2Type RSUAddr;
 *     bool COLevel;
 * }
 * </pre>
 */
class VEINS_API RSUCOLevel : public ::veins::BaseFrame1609_4
{
  protected:
    LAddress::L2Type RSUAddr;
    bool COLevel;

  private:
    void copy(const RSUCOLevel& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RSUCOLevel&);

  public:
    RSUCOLevel(const char *name=nullptr, short kind=0);
    RSUCOLevel(const RSUCOLevel& other);
    virtual ~RSUCOLevel();
    RSUCOLevel& operator=(const RSUCOLevel& other);
    virtual RSUCOLevel *dup() const override {return new RSUCOLevel(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual LAddress::L2Type& getRSUAddr();
    virtual const LAddress::L2Type& getRSUAddr() const {return const_cast<RSUCOLevel*>(this)->getRSUAddr();}
    virtual void setRSUAddr(const LAddress::L2Type& RSUAddr);
    virtual bool getCOLevel() const;
    virtual void setCOLevel(bool COLevel);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RSUCOLevel& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RSUCOLevel& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>veins/modules/application/traci/RSUCluster/CarComputationOffloading.msg:65</tt> by nedtool.
 * <pre>
 * packet CarCOAck extends BaseFrame1609_4
 * {
 *     int taskID;
 *     long CarAddr;
 * }
 * </pre>
 */
class VEINS_API CarCOAck : public ::veins::BaseFrame1609_4
{
  protected:
    int taskID;
    long CarAddr;

  private:
    void copy(const CarCOAck& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CarCOAck&);

  public:
    CarCOAck(const char *name=nullptr, short kind=0);
    CarCOAck(const CarCOAck& other);
    virtual ~CarCOAck();
    CarCOAck& operator=(const CarCOAck& other);
    virtual CarCOAck *dup() const override {return new CarCOAck(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getTaskID() const;
    virtual void setTaskID(int taskID);
    virtual long getCarAddr() const;
    virtual void setCarAddr(long CarAddr);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CarCOAck& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CarCOAck& obj) {obj.parsimUnpack(b);}

} // namespace veins

#endif // ifndef __VEINS_CARCOMPUTATIONOFFLOADING_M_H


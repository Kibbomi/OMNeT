//
// Generated file, do not edit! Created by nedtool 5.6 from veins/modules/application/traci/RSUCluster/RSUConnection.msg.
//

#ifndef __VEINS_RSUCONNECTION_M_H
#define __VEINS_RSUCONNECTION_M_H

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
#include <string>
// }}


namespace veins {

/**
 * Class generated from <tt>veins/modules/application/traci/RSUCluster/RSUConnection.msg:31</tt> by nedtool.
 * <pre>
 * packet RSUAdvertisement extends BaseFrame1609_4
 * {
 *     //SYN
 *     string RSUName;
 *     int y;
 *     int x;
 * 
 *     //Time
 *     simtime_t advertisementTime;
 * }
 * </pre>
 */
class VEINS_API RSUAdvertisement : public ::veins::BaseFrame1609_4
{
  protected:
    ::omnetpp::opp_string RSUName;
    int y;
    int x;
    ::omnetpp::simtime_t advertisementTime;

  private:
    void copy(const RSUAdvertisement& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RSUAdvertisement&);

  public:
    RSUAdvertisement(const char *name=nullptr, short kind=0);
    RSUAdvertisement(const RSUAdvertisement& other);
    virtual ~RSUAdvertisement();
    RSUAdvertisement& operator=(const RSUAdvertisement& other);
    virtual RSUAdvertisement *dup() const override {return new RSUAdvertisement(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getRSUName() const;
    virtual void setRSUName(const char * RSUName);
    virtual int getY() const;
    virtual void setY(int y);
    virtual int getX() const;
    virtual void setX(int x);
    virtual ::omnetpp::simtime_t getAdvertisementTime() const;
    virtual void setAdvertisementTime(::omnetpp::simtime_t advertisementTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RSUAdvertisement& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RSUAdvertisement& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>veins/modules/application/traci/RSUCluster/RSUConnection.msg:42</tt> by nedtool.
 * <pre>
 * packet CARConnectionReq extends BaseFrame1609_4
 * {
 *     //SYN + ACK
 *     string CarName;
 * }
 * </pre>
 */
class VEINS_API CARConnectionReq : public ::veins::BaseFrame1609_4
{
  protected:
    ::omnetpp::opp_string CarName;

  private:
    void copy(const CARConnectionReq& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CARConnectionReq&);

  public:
    CARConnectionReq(const char *name=nullptr, short kind=0);
    CARConnectionReq(const CARConnectionReq& other);
    virtual ~CARConnectionReq();
    CARConnectionReq& operator=(const CARConnectionReq& other);
    virtual CARConnectionReq *dup() const override {return new CARConnectionReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getCarName() const;
    virtual void setCarName(const char * CarName);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CARConnectionReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CARConnectionReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>veins/modules/application/traci/RSUCluster/RSUConnection.msg:48</tt> by nedtool.
 * <pre>
 * packet CARConnectionResp extends BaseFrame1609_4
 * {
 *     //ACK
 *     bool success;
 * }
 * </pre>
 */
class VEINS_API CARConnectionResp : public ::veins::BaseFrame1609_4
{
  protected:
    bool success;

  private:
    void copy(const CARConnectionResp& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CARConnectionResp&);

  public:
    CARConnectionResp(const char *name=nullptr, short kind=0);
    CARConnectionResp(const CARConnectionResp& other);
    virtual ~CARConnectionResp();
    CARConnectionResp& operator=(const CARConnectionResp& other);
    virtual CARConnectionResp *dup() const override {return new CARConnectionResp(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual bool getSuccess() const;
    virtual void setSuccess(bool success);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CARConnectionResp& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CARConnectionResp& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>veins/modules/application/traci/RSUCluster/RSUConnection.msg:54</tt> by nedtool.
 * <pre>
 * packet CARDisconnectionReq extends BaseFrame1609_4
 * {
 *     //FIN
 *     string CarName;
 * }
 * </pre>
 */
class VEINS_API CARDisconnectionReq : public ::veins::BaseFrame1609_4
{
  protected:
    ::omnetpp::opp_string CarName;

  private:
    void copy(const CARDisconnectionReq& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CARDisconnectionReq&);

  public:
    CARDisconnectionReq(const char *name=nullptr, short kind=0);
    CARDisconnectionReq(const CARDisconnectionReq& other);
    virtual ~CARDisconnectionReq();
    CARDisconnectionReq& operator=(const CARDisconnectionReq& other);
    virtual CARDisconnectionReq *dup() const override {return new CARDisconnectionReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getCarName() const;
    virtual void setCarName(const char * CarName);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CARDisconnectionReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CARDisconnectionReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>veins/modules/application/traci/RSUCluster/RSUConnection.msg:60</tt> by nedtool.
 * <pre>
 * packet CARDisconnectionResp extends BaseFrame1609_4
 * {
 *     //FIN ACK
 *     string RSUName;	//이거 없어도 될 것 같음.
 * }
 * </pre>
 */
class VEINS_API CARDisconnectionResp : public ::veins::BaseFrame1609_4
{
  protected:
    ::omnetpp::opp_string RSUName;

  private:
    void copy(const CARDisconnectionResp& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CARDisconnectionResp&);

  public:
    CARDisconnectionResp(const char *name=nullptr, short kind=0);
    CARDisconnectionResp(const CARDisconnectionResp& other);
    virtual ~CARDisconnectionResp();
    CARDisconnectionResp& operator=(const CARDisconnectionResp& other);
    virtual CARDisconnectionResp *dup() const override {return new CARDisconnectionResp(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getRSUName() const;
    virtual void setRSUName(const char * RSUName);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CARDisconnectionResp& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CARDisconnectionResp& obj) {obj.parsimUnpack(b);}

} // namespace veins

#endif // ifndef __VEINS_RSUCONNECTION_M_H


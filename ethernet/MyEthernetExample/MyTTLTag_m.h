//
// Generated file, do not edit! Created by nedtool 5.6 from inet/applications/ethernet/MyEthernetExample/MyTTLTag.msg.
//

#ifndef __INET_MYTTLTAG_M_H
#define __INET_MYTTLTAG_M_H

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

class CreationTTLTag;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/TagBase_m.h" // import inet.common.TagBase


namespace inet {

/**
 * Class generated from <tt>inet/applications/ethernet/MyEthernetExample/MyTTLTag.msg:21</tt> by nedtool.
 * <pre>
 * class CreationTTLTag extends TagBase
 * {
 *     unsigned int ttl;
 * }
 * </pre>
 */
class INET_API CreationTTLTag : public ::inet::TagBase
{
  protected:
    unsigned int ttl = 0;

  private:
    void copy(const CreationTTLTag& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CreationTTLTag&);

  public:
    CreationTTLTag();
    CreationTTLTag(const CreationTTLTag& other);
    virtual ~CreationTTLTag();
    CreationTTLTag& operator=(const CreationTTLTag& other);
    virtual CreationTTLTag *dup() const override {return new CreationTTLTag(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getTtl() const;
    virtual void setTtl(unsigned int ttl);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CreationTTLTag& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CreationTTLTag& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_MYTTLTAG_M_H


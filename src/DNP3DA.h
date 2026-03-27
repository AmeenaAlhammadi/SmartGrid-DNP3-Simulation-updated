#ifndef __FIRSTBASELINE_DNP3DA_H
#define __FIRSTBASELINE_DNP3DA_H

#include <omnetpp.h>

using namespace omnetpp;

class DNP3DA : public cSimpleModule
{
  private:
    int numMeters = 0;
    simtime_t processingDelay;
    simsignal_t packetDelaySignal;
    int receivedEventCount = 0;

    long eventBytesTotal = 0;
    long ackBytesTotal = 0;
    long confirmBytesTotal = 0;
    long tcpAckBytesTotal = 0;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    void sendControlMessage(const char *name, const char *type, int meterId, int seq, int bytes);
};

#endif

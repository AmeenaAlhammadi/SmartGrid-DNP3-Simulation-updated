#ifndef __FIRSTBASELINE_DNP3DA_H
#define __FIRSTBASELINE_DNP3DA_H

#include <omnetpp.h>

using namespace omnetpp;

class DNP3DA : public cSimpleModule
{
  private:
    int numMeters = 0;
    simtime_t processingDelay;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    void sendControlMessage(const char *name, const char *type, int meterId, int seq, int bytes);
};

#endif

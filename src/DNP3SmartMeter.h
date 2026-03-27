#ifndef DNP3SMARTMETER_H
#define DNP3SMARTMETER_H

#include <omnetpp.h>
#include "DNP3Packet_m.h"

using namespace omnetpp;

class DNP3SmartMeter : public cSimpleModule
{
  private:
    cMessage *ackTimer = nullptr;
    cMessage *eventTimer = nullptr;

    int seq = 0;
    int packetsSent = 0;
    int totalPackets = 0;
    int eventBytes = 442;
    simtime_t ackTimeout;
    simtime_t stopGenerationTime;

    bool waitingForAck = false;
    int currentSeq = -1;

    simtime_t currentPacketGenTime;
    int retransmissionCount = 0;
    int generatedEventCount = 0;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    void sendEventReport(bool isRetransmission);
    void sendTcpAck(int meterId, int seq);
};

#endif

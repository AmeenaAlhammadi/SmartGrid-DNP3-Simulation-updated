#ifndef CONCATENATOR_H
#define CONCATENATOR_H

#include <omnetpp.h>
#include "DNP3Packet_m.h"

using namespace omnetpp;

class Concatenator : public cSimpleModule
{
  private:
    cQueue daQueue;
    cMessage *endTxEvent = nullptr;
    bool daBusy = false;
    int maxQueueSize = 50;
    int droppedPackets = 0;
    simsignal_t queueLengthSignal;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    void enqueueFromMeter(Dnp3Packet *pkt);
    void startNextTransmissionToDA();
    void forwardToMeter(Dnp3Packet *pkt);
};

#endif

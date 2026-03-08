#include <omnetpp.h>
#include "DNP3SmartMeter.h"
#include <cstring>

using namespace omnetpp;

Define_Module(DNP3SmartMeter);
void DNP3SmartMeter::initialize()
{
    ackTimer = new cMessage("ackTimeout");
    eventTimer = new cMessage("eventTimer");

    seq = 0;
    currentSeq = -1;
    waitingForAck = false;
    packetsSent = 0;

    totalPackets = par("totalPackets");
    ackTimeout = par("ackTimeout");
    eventBytes = par("eventBytes");

    scheduleAt(simTime() + par("eventInterval").doubleValue(), eventTimer);
}

void DNP3SmartMeter::sendEventReport(bool isRetransmission)
{
    auto *pkt = new Dnp3Packet(isRetransmission ? "retransmittedEventReport" : "eventReport");
    pkt->setMeterId(par("meterId").intValue());
    pkt->setSeq(currentSeq);
    pkt->setMsgType("EVENT_REPORT");
    pkt->setBurst(false);
    pkt->setByteLength(eventBytes);

    cGate *outGate = gate("interface$o");
    simtime_t txDelay = 0;
    cChannel *ch = outGate->getTransmissionChannel();
    if (ch != nullptr) {
        simtime_t finishTime = ch->getTransmissionFinishTime();
        if (finishTime > simTime())
            txDelay = finishTime - simTime();
    }

    sendDelayed(pkt, txDelay, outGate);

    EV << "Smart meter " << par("meterId").intValue()
       << (isRetransmission ? " retransmitted " : " sent ")
       << "EVENT_REPORT seq=" << currentSeq
       << " size=" << eventBytes << " bytes\n";
}

void DNP3SmartMeter::sendTcpAck(int meterId, int seqNumber)
{
    auto *pkt = new Dnp3Packet("tcpAck");
    pkt->setMeterId(meterId);
    pkt->setSeq(seqNumber);
    pkt->setMsgType("TCP_ACK");
    pkt->setBurst(false);

    // Updated TCP ACK size
    pkt->setByteLength(58);

    cGate *outGate = gate("interface$o");

    simtime_t txDelay = 0;
    cChannel *ch = outGate->getTransmissionChannel();

    if (ch != nullptr) {
        simtime_t finishTime = ch->getTransmissionFinishTime();
        if (finishTime > simTime())
            txDelay = finishTime - simTime();
    }

    sendDelayed(pkt, txDelay, outGate);

    EV << "Smart meter "
       << meterId
       << " sent TCP_ACK for seq="
       << seqNumber
       << " size=58 bytes\n";
}

void DNP3SmartMeter::handleMessage(cMessage *msg)
{
    if (msg == eventTimer) {
        if (!waitingForAck && packetsSent < totalPackets) {
            currentSeq = seq;
            waitingForAck = true;

            sendEventReport(false);
            scheduleAt(simTime() + ackTimeout, ackTimer);
        }

        if (packetsSent < totalPackets)
            scheduleAt(simTime() + par("eventInterval").doubleValue(), eventTimer);

        return;
    }

    if (msg == ackTimer) {
        if (waitingForAck) {
            EV << "ACK timeout at smart meter " << par("meterId").intValue()
               << " for seq=" << currentSeq << ", retransmitting event report\n";

            sendEventReport(true);
            scheduleAt(simTime() + ackTimeout, ackTimer);
        }
        return;
    }

    auto *pkt = check_and_cast<Dnp3Packet *>(msg);
    const char *type = pkt->getMsgType();

    if (strcmp(type, "ACK") == 0 && pkt->getSeq() == currentSeq) {
        waitingForAck = false;
        cancelEvent(ackTimer);
        packetsSent++;
        seq++;

        EV << "Smart meter " << par("meterId").intValue()
           << " received ACK for seq=" << pkt->getSeq() << "\n";
    }
    else if (strcmp(type, "CONFIRM") == 0) {
        EV << "Smart meter " << par("meterId").intValue()
           << " received CONFIRM for seq=" << pkt->getSeq() << "\n";

        sendTcpAck(pkt->getMeterId(), pkt->getSeq());
    }

    delete pkt;
}

void DNP3SmartMeter::finish()
{
    cancelAndDelete(ackTimer);
    cancelAndDelete(eventTimer);
}

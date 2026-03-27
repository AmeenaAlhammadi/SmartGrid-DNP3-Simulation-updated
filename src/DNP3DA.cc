#include <omnetpp.h>
#include "DNP3DA.h"
#include "DNP3Packet_m.h"
#include <cstring>

using namespace omnetpp;

Define_Module(DNP3DA);

void DNP3DA::initialize()
{
    numMeters = par("numMeters");
    processingDelay = par("processingDelay");
    packetDelaySignal = registerSignal("packetDelay");
}

void DNP3DA::sendControlMessage(const char *name, const char *type, int meterId, int seq, int bytes)
{
    auto *pkt = new Dnp3Packet(name);
    pkt->setMsgType(type);
    pkt->setMeterId(meterId);
    pkt->setSeq(seq);
    pkt->setByteLength(bytes);

    if (strcmp(type, "ACK") == 0)
        ackBytesTotal += bytes;
    else if (strcmp(type, "CONFIRM") == 0)
        confirmBytesTotal += bytes;

    cGate *outGate = gate("interface$o");

    simtime_t txDelay = processingDelay;

    cChannel *ch = outGate->getTransmissionChannel();
    if (ch != nullptr) {
        simtime_t finishTime = ch->getTransmissionFinishTime();
        if (finishTime > simTime())
            txDelay += (finishTime - simTime());
    }

    sendDelayed(pkt, txDelay, outGate);
}

void DNP3DA::handleMessage(cMessage *msg)
{
    auto *pkt = dynamic_cast<Dnp3Packet *>(msg);
    if (!pkt) {
        delete msg;
        return;
    }

    if (strcmp(pkt->getMsgType(), "EVENT_REPORT") == 0) {

        receivedEventCount++;

        eventBytesTotal += pkt->getByteLength();

        simtime_t delay = simTime() - pkt->getGenTime();
        emit(packetDelaySignal, delay);

        EV << "DA received EVENT_REPORT from meter "
           << pkt->getMeterId()
           << " seq=" << pkt->getSeq()
           << " size=" << pkt->getByteLength()
           << " bytes"
           << " delay=" << delay
           << " retransmitted=" << (pkt->getRetransmitted() ? "true" : "false")
           << "\n";

        sendControlMessage("ack", "ACK", pkt->getMeterId(), pkt->getSeq(), 68);
        sendControlMessage("confirm", "CONFIRM", pkt->getMeterId(), pkt->getSeq(), 58);
    }
    else if (strcmp(pkt->getMsgType(), "TCP_ACK") == 0) {

        tcpAckBytesTotal += pkt->getByteLength();

        EV << "DA received TCP_ACK from meter "
           << pkt->getMeterId()
           << " seq=" << pkt->getSeq()
           << " size=" << pkt->getByteLength()
           << " bytes\n";
    }

    delete pkt;
}

void DNP3DA::finish()
{
    recordScalar("receivedEventPackets", receivedEventCount);
    recordScalar("eventBytesTotal", eventBytesTotal);
    recordScalar("ackBytesTotal", ackBytesTotal);
    recordScalar("confirmBytesTotal", confirmBytesTotal);
    recordScalar("tcpAckBytesTotal", tcpAckBytesTotal);
}


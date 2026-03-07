#include "Concatenator.h"
#include "DNP3Packet_m.h"
#include <cstring>

Define_Module(Concatenator);

void Concatenator::initialize()
{
    endTxEvent = new cMessage("endTxEvent");
    daBusy = false;
}

void Concatenator::enqueueFromMeter(Dnp3Packet *pkt)
{
    daQueue.insert(pkt);

    EV << "Concatenator received packet from meter "
       << pkt->getMeterId()
       << " type=" << pkt->getMsgType()
       << " seq=" << pkt->getSeq() << "\n";

    if (!daBusy) {
        startNextTransmissionToDA();
    }
}

void Concatenator::startNextTransmissionToDA()
{
    if (daQueue.isEmpty()) {
        daBusy = false;
        return;
    }

    auto *pkt = check_and_cast<Dnp3Packet *>(daQueue.pop());
    cGate *outGate = gate("DAInterface$o");

    EV << "Concatenator sent packet immediately to DA: meter="
       << pkt->getMeterId()
       << " type=" << pkt->getMsgType()
       << " seq=" << pkt->getSeq() << "\n";

    send(pkt, outGate);
    daBusy = true;

    cChannel *ch = outGate->getTransmissionChannel();
    if (ch != nullptr) {
        simtime_t finishTime = ch->getTransmissionFinishTime();
        if (finishTime > simTime()) {
            scheduleAt(finishTime, endTxEvent);
        } else {
            scheduleAt(simTime(), endTxEvent);
        }
    } else {
        scheduleAt(simTime(), endTxEvent);
    }
}

void Concatenator::forwardToMeter(Dnp3Packet *pkt)
{
    int meterId = pkt->getMeterId();

    if (meterId < 0 || meterId >= gateSize("MeterInterface")) {
        delete pkt;
        return;
    }

    cGate *outGate = gate("MeterInterface$o", meterId);

    simtime_t txDelay = 0;
    cChannel *ch = outGate->getTransmissionChannel();
    if (ch != nullptr) {
        simtime_t finishTime = ch->getTransmissionFinishTime();
        if (finishTime > simTime())
            txDelay = finishTime - simTime();
    }

    EV << "Concatenator forwarded packet from DA to meter "
       << meterId
       << " type=" << pkt->getMsgType()
       << " seq=" << pkt->getSeq() << "\n";

    sendDelayed(pkt, txDelay, outGate);
}

void Concatenator::handleMessage(cMessage *msg)
{
    if (msg == endTxEvent) {
        daBusy = false;
        startNextTransmissionToDA();
        return;
    }

    auto *pkt = check_and_cast<Dnp3Packet *>(msg);
    cGate *arrivalGate = pkt->getArrivalGate();

    if (!arrivalGate) {
        delete pkt;
        return;
    }

    const char *gateName = arrivalGate->getBaseName();

    if (strcmp(gateName, "MeterInterface") == 0) {
        enqueueFromMeter(pkt);
        return;
    }

    if (strcmp(gateName, "DAInterface") == 0) {
        forwardToMeter(pkt);
        return;
    }

    delete pkt;
}

void Concatenator::finish()
{
    cancelAndDelete(endTxEvent);

    while (!daQueue.isEmpty()) {
        auto *pkt = check_and_cast<cPacket *>(daQueue.pop());
        delete pkt;
    }
}

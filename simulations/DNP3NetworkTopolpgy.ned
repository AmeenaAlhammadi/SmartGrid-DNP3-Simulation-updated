package basicbaseline.simulations;

import basicbaseline.DNP3SmartMeter;
import basicbaseline.DNP3DA;
import basicbaseline.Concatenator;

network DNP3NetworkTopology
{
    parameters:
        int numMeters = default(5);

        @display("bgb=436,366");
    submodules:
        meter[numMeters]: DNP3SmartMeter {
            parameters:
                meterId = index;
        }

        concentrator: Concatenator {

        }
        distAuto: DNP3DA {
            parameters:
                numMeters = parent.numMeters;
        }

    connections:
        for i=0..numMeters-1 {
            meter[i].interface <--> {  datarate = 65kbps; delay = 2ms; } <--> concentrator.MeterInterface++;
        }

        concentrator.DAInterface <--> {  datarate = 128kbps; delay = 5ms; } <--> distAuto.interface;
}

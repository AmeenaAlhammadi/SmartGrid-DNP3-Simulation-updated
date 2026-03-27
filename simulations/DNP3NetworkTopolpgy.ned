package basicbaseline.simulations;

import basicbaseline.DNP3SmartMeter;
import basicbaseline.DNP3DA;
import basicbaseline.Concatenator;

network DNP3NetworkTopology
{
    parameters:
        int numMeters = default(5);

    submodules:
        meter[numMeters]: DNP3SmartMeter {
            parameters:
                meterId = index;
        }

        Concatenator: Concatenator {
            @display("p=292,154");
        }
        distAuto: DNP3DA {
            parameters:
                numMeters = parent.numMeters;
                @display("p=54,390");
        }

    connections:
        for i=0..numMeters-1 {
            meter[i].interface <--> {  datarate = 65kbps; delay = 2ms; } <--> Concatenator.MeterInterface++;
        }

        Concatenator.DAInterface <--> {  datarate = 128kbps; delay = 5ms; } <--> distAuto.interface;
}

//
// Created by Ivan Hargesheimer on 9/17/25.
// Morehead State University Rocketry Club
// Payloads and Comms Team
// This implements a unified interface for the sensors that the rocket has
//

module;
// #include <wiringPy.h>
#include <array>
export module SensorModule:Sensor;

namespace flight_computer {
    //placeholder for the real data packet format
    using DataFormat = double;
    export template<unsigned NumberOfPins>
    class Sensor {
        using pin_array = std::array<int, NumberOfPins>;
    public:
    explicit Sensor(pin_array &&pins)
        : _pin_indicies{std::forward<pin_array>(pins)} {}
        // Get_Data_From_Pins
        DataFormat Get_Data_From_Sensor() {
            
        }
    private:
        pin_array _pin_indicies;
    };
}

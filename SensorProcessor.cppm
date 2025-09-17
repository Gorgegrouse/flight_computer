//
// Created by Ivan Hargesheimer on 9/17/25.
// Morehead State University Rocketry Club
// Payloads and Comms Team
// This implements an sensor-agnostic interface that is intendedd
// to be consumed in conjunction with a std::jthread

module;
#include <string_view>
#include <fstream>
export module SensorModule:SensorProcessor;
import :Sensor;
namespace flight_computer {
    // using SensorStatus::
    export template<unsigned NumberOfPinsInSensor>
    void sensor_processor(Sensor<NumberOfPinsInSensor> &sensor, const std::string_view &&filename) {
        std::ofstream data_file(std::forward<const std::string_view>(filename));
        sensor.Recieve_Data();
    }
}


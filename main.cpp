//Ivan Hargesheimer
//Morehead State University Rocketry Club
//Communications and Payloads Team

#include <array>
#include <thread>
#include <libusb.h>

import SensorModule;
// import SensorProcessor;
// import Sensor;
// import PinMapper;

[[noreturn]] int main() {
    enum class SensorStatus {
        FULLY_FUNCTIONING,
        SENSOR_ERROR,
        TRANSMITER_ERROR
    };

    //setup raspberry pi pins
    wiringPiSetupGpio();

    
    libusb_context *context = nullptr;

    constexpr unsigned number_of_pins_on_raspberry_pi = 40u;

    //initialize sensors
    

    //process sensors in parallel
    {
        using std::jthread;
        using flight_computer::sensor_processor;
        // jthread accelerator_processor(sensor_processor,  );

        
    }

    std::array<int, number_of_pins_on_raspberry_pi> pin_mapping{};
    //main loop for running the 
    while (true) {
        
    }
    
}
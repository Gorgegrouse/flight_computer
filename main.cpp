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

    constexpr auto PinsForAccelerometer = {3,5};
    //Sda 2
    //clock 3
    enum AccelerometerPins {
        SDA = 2,
        CLOCK = 3,
        OUTPUT_1 = 6,
        OUTPUT_2 = 4
    };
    //accelerometer
    pinMode(CLOCK, GPIO_CLOCK);
    pinMode(SDA, INPUT);
    pinMode(OUTPUT_1, OUTPUT);
    pinMode(OUTPUT_2, OUTPUT);
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
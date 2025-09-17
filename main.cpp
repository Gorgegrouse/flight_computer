//Ivan Hargesheimer
//Morehead State University Rocketry Club
//Communications and Payloads Team

#include <array>
#include <libusb.h>

[[noreturn]] int main() {
    enum class ComputerStatus {
        FULLY_FUNCTIONING,
        SENSOR_ERROR,
        TRANSMITER_ERROR
    };
    libusb_context *context = nullptr;

    constexpr unsigned number_of_pins_on_raspberry_pi = 40u;

    std::array<int, number_of_pins_on_raspberry_pi> pin_mapping; 
    //main loop for running the 
    while (true) {
        
    }
    
}
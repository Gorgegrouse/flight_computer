//
// Created by Ivan Hargesheimer on 9/17/25.
//
module;
#include <ranges>
export module PinMapper;
import Sensor;
namespace flight_computer {
    export template <size_t TotalNumberOfPinsOnRaspberryPi>
    class PinMapper {
    public:
        template<unsigned NumberOfPinsToReserve>
        void Reserve_Pins(const unsigned beginning_index_of_raspberry_pi_pin_range_to_reserve, const unsigned end_index_of_rasberry_pi_pin_range_to_reserve, Sensor<NumberOfPinsToReserve> &sensor) {
            const auto pin_range = std::views::iota(beginning_index_of_raspberry_pi_pin_range_to_reserve, end_index_of_rasberry_pi_pin_range_to_reserve);
            std::array<int, NumberOfPinsToReserve> reserved_pins_on_sensor = sensor.Reserve_Pins(pin_range);
            for (const auto [pin_in_pi_range, pin_in_sensor_range] : std::views::zip(pin_range, reserved_pins_on_sensor)) {
                _pins_on_raspberry_pi_to_sensor_pins[pin_in_pi_range] = pin_in_sensor_range;
            }
        }
    private:
        std::array<int, TotalNumberOfPinsOnRaspberryPi> _pins_on_raspberry_pi_to_sensor_pins;
    };
}
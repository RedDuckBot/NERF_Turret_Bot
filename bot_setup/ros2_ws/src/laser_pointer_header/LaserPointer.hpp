#ifndef LASERPOINTER
#define LASERPOINTER

#include "libgpio/DigitalOutput.hpp"

namespace laser_gpio
{
    class LaserPointer:
    {
        public:
            LaserPointer(unint32_t gpioPin);

            void on();
            void off();

        private:
            DigitalOutput laserPin_;
    }
}
#endif LASERPOINTER
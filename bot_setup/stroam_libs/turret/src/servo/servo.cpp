#include "servo.hpp"

namespace stroams_servo
{
    Servo::Servo(unsigned int servoPin, unsigned int min_pulse_width, 
        unsigned int max_pulse_width, int starting_angle, 
        const std::string& servoName): 
            Device(servoPin, servoName) 
    {
        this -> starting_angle_ = starting_angle;
        this -> servoPin_ = servoPin;
        this -> min_pulse_width_ = min_pulse_width;
        this -> max_pulse_width_ = max_pulse_width;

    }

    Servo::~Servo()
    {
        set_servo_pulsewidth(getGPIOHandle(), servoPin_, 
            get_pwm_value_from_angle(starting_angle_)); 
        
        set_servo_pulsewidth(getGPIOHandle(), servoPin_, 0); //stop servo
    }

    void Servo::rotate_to_pos(int angle)
    {
        unsigned pwm_value = get_pwm_value_from_angle(angle);
        set_servo_pulsewidth(getGPIOHandle(), servoPin_, pwm_value);
    }

    unsigned int Servo::get_pwm_value_from_angle(int angle)
    {
        //Pulse widths are in microseconds
        double x;
        int pwm_value;
        double pwm_range = max_pulse_width_ - min_pulse_width_;

        x = angle / 180.0;
        x = pwm_range * x;
        pwm_value = (int) (min_pulse_width_ + x);

        if (pwm_value > max_pulse_width_)
        {
            pwm_value = max_pulse_width_;
        }

        if (pwm_value < min_pulse_width_)
        {
            pwm_value = min_pulse_width_;
        }

        return pwm_value;
    }


}
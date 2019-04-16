
/*

Copyright (c) 2019, Society of Robotics and Automation, VJTI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#include "SERVO.h"

void mcpwm_example_gpio_initialize()
    {
        printf("initializing mcpwm servo control gpio......\n");

        //Set GPIO PINS as PWM0A, to which servo is connected
        mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, SERVO_PIN_1);    
        mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, SERVO_PIN_2);
        mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, SERVO_PIN_3);
        printf("Configuring Initial Parameters of mcpwm......\n");

        //Configure pwm
        mcpwm_config_t pwm_config;
        pwm_config.frequency = 50;    //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
        pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
        pwm_config.cmpr_b = 0;    //duty cycle of PWMxb = 0
        pwm_config.counter_mode = MCPWM_UP_COUNTER;
        pwm_config.duty_mode = MCPWM_DUTY_MODE_0;

        //Assign the configurations to MCPWM_UNIT
        mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config); 
        mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);     
    }

//Convert angles in degrees to angles in PWM for micro servo
uint32_t micro_servo_per_degree_init(uint32_t degree_of_rotation)
    {
        uint32_t cal_pulsewidth_micro = 0;
        cal_pulsewidth_micro = (MICRO_SERVO_MIN_PULSEWIDTH + 2*(((MICRO_SERVO_MAX_PULSEWIDTH - MICRO_SERVO_MIN_PULSEWIDTH) * (degree_of_rotation)) / (SERVO_MAX_DEGREE)));
        return cal_pulsewidth_micro;
    }

//Convert angles in degrees to angles in PWM for servo
uint32_t servo_per_degree_init(uint32_t degree_of_rotation)
    {
        uint32_t cal_pulsewidth = 0;
        cal_pulsewidth = (SERVO_MIN_PULSEWIDTH + 2*(((SERVO_MAX_PULSEWIDTH- SERVO_MIN_PULSEWIDTH) * (degree_of_rotation)) / (SERVO_MAX_DEGREE)));
        return cal_pulsewidth;
    }

//Write PWM values to all the Servos
void mcpwm_example_servo_control(int theta1,int theta2,int theta3)
    { 
        PWM1 = servo_per_degree_init(theta1);
        PWM2 = micro_servo_per_degree_init(theta2);
        PWM3 = micro_servo_per_degree_init(theta3);
        mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, PWM1);
        mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, PWM2);
        mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, PWM3);
    }

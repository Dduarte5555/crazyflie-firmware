#include "mbed.h"
#include "crazyflie.h"

PwmOut motor1(MOTOR1);
float control_motor(float omega){
    float result = (1.4*pow(10, -7) * omega);
    return result;
}

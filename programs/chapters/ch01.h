#include "mbed.h"
#include "crazyflie.h"
#include "pin_names.h"

// Define all LEDs as digital output objects
DigitalOut ledRR(LED_RED_R,!false);
DigitalOut ledRL(LED_RED_L,!false);
DigitalOut ledGR(LED_GREEN_R,!false);
DigitalOut ledGL(LED_GREEN_L,!false);
DigitalOut ledBL(LED_BLUE_L,!false);

// Define all motors as PWM objects
PwmOut motor1(MOTOR1);
PwmOut motor2(MOTOR2);
PwmOut motor3(MOTOR3);
PwmOut motor4(MOTOR4);

// Main program
int main()
{
    // Blink blue LED indicating inicialization (5 seconds)
    int i=0;
        while(i<5) 
    {
        ledBL = !ledBL;
        wait(0.5);
        ledBL = !ledBL;
        wait(0.5);
        i+=1;
    }
    ledBL = !ledBL;
    
    // Turn on red LEDs indicating motors are armed
    ledRL=! ledRL;
    wait(1);
    ledRR=! ledRR;
    wait(1);

    
    // Test all motors with different frequencies (to make different noises)
    motor1.period(1.0/400);
    motor1=0.2;
    wait(0.5);
    motor2.period(1.0/600);
    motor2=0.2;
    wait(0.5);
    motor3.period(1.0/800);
    motor3=0.2;
    wait(0.5);
    motor4.period(1.0/1000);
    motor4=0.2;
    wait(1);

    motor1=0;
    motor2=0;
    motor3=0;
    motor4=0;
    
    
    // Turn off red LEDs indicating motors are disarmed
    ledRL=! ledRL;
    wait(1);
    ledRR=! ledRR;
    wait(1);
    
    // Blink green LEDs indicating end of program
        while(i<7) 
    {
        ledGL = !ledGL;
        ledGR = !ledGR;
        wait(0.5);
        ledGL = !ledGL;
        ledGR = !ledGR;
        wait(0.5);
        i+=1;
    }

    while(true)
    {
        
    }
}

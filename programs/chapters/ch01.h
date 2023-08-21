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

// Define notes in Spanish Nomenclature

const int la = 110; //La
const int d = 131;//Do
const int r = 147;//Re
const int mi = 165;//Mi
const int f = 174;//Fa
const int s = 196;//Sol
const int laa = 220;//La
const int lS = 233;//La#
const int si = 247;//si
const int Do = 262;//do
const int Re = 294; //re
const int Mi = 329;//Mi
const int Fa = 349;//Fa
const int Sol = 392;//Sol
const int La = 440;//La
const int LaS = 466;//La#
const int Si = 494;//si
const int Doo = 523;//do

//startup song

void beep1(int freq, float period){
    motor1.period(1.0/((float) freq));
    motor1 = 0.2;
    wait_ms(period);
    motor1 = 0.0;
    //wait(0.05);
}

void beep2(int freq, float period){
    motor2.period(1.0/((float) freq));
    motor2 = 0.2;
    wait_ms(period);
    motor2 = 0.0;
    //wait(0.05);
}

void beep3(int freq, float period){
    motor3.period(1.0/((float) freq));
    motor3 = 0.2;
    wait_ms(period);
    motor3 = 0.0;
    //wait(0.05);
}

void beep4(int freq, float period){
    motor4.period(1.0/((float) freq));
    motor4 = 0.2;
    wait_ms(period);
    motor4 = 0.0;
    //wait(0.05);
}

void Cucaracha() {
  beep1(Do, 250);
  beep2(Do, 250);
  beep3(Do, 250);
  beep4(Fa, 250);
  wait_ms(250);
  beep1(La, 250);
  wait_ms(250);
  beep2(Do, 250);
  beep3(Do, 250);
  beep4(Do, 250);
  wait_ms(250);
  beep1(Fa, 500);
  beep2(La, 1250);
  wait_ms(500);
  beep3(Fa, 250);
  beep4(Fa, 250);
  beep1(Mi, 250);
  beep2(Mi, 250);
  beep3(Re, 250);
  beep4(Re, 250);
  beep1(Do, 1000);
  wait_ms(250);
  beep2(Do, 250);
  beep3(Do, 250);
  beep4(Do, 250);
  beep1(Mi, 500);
  wait_ms(250);
  beep2(Sol, 250);
  wait_ms(250);
  wait_ms(250);
  beep3(Do, 250);
  beep4(Do, 250);
  beep1(Do, 250);
  beep2(Mi, 500);
  wait_ms(250);
  beep3(Sol, 1250);
  wait_ms(500);
  beep4(Do, 250);
  beep1(Re, 250);
  beep2(Do, 250);
  beep3(lS, 250);
  beep4(La, 250);
  beep1(Sol, 250);
  beep2(Fa, 500);
  wait_ms(2000);
  beep3(Do, 250);
  beep4(Do, 250);
  beep1(Fa, 250);
  beep2(Fa, 250);
  beep3(La, 250);
  beep4(La, 250);
  beep1(Do, 500);
  wait_ms(250);
  beep2(La, 1250);
  wait_ms(250);
  beep2(Do, 500);
  beep3(Re, 250);
  beep4(Do, 250);
  beep1(lS, 250);
  beep2(La, 250);
  beep3(Do, 250);
  beep4(lS, 500);
  wait_ms(250);
  beep1(Sol, 1250);
  wait_ms(500);
  beep2(Do, 250);
  beep3(Do, 250);
  beep4(Mi, 250);
  beep1(Mi, 250);
  beep2(Sol, 250);
  beep3(Sol, 250);
  beep4(lS, 500);
  wait_ms(250);
  beep1(Sol, 1250);
  wait_ms(250);
  beep2(Do, 500);
  beep3(Re, 250);
  beep4(Do, 250);
  beep1(lS, 250);
  beep2(La, 250);
  beep3(Sol, 250);
  beep4(Fa, 1000);
  wait_ms(2000);

}

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

    
    //Test all motors with different frequencies (to make different noises)
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

    Cucaracha();

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


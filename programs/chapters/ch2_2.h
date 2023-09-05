#include "mbed.h"
#include "crazyflie.h"

// Define o motor como saída PWM
PwmOut motor1(MOTOR1);
PwmOut motor2(MOTOR2);
PwmOut motor3(MOTOR3);
PwmOut motor4(MOTOR4);

// Converte velocidade angular (rad/s) em sinal PWM (%)
float control_motor(float omega){
    float result = a2*omega*omega;
    return result;
}

// Main Program
int main(){

    // Frequência PWM para 500Hz
    wait(2);
    motor1.period(1.0/500.0);
    motor2.period(1.0/500.0);
    motor3.period(1.0/500.0);
    motor4.period(1.0/500.0);

    // Liga o motor com velocidade angular de 1000 rad/s por 5 seg
    motor1 = control_motor(1000.0);
    motor2 = control_motor(2000.0);
    motor3 = control_motor(1000.0);
    motor4 = control_motor(2000.0);
    wait(5);

    // Desliga o motor
    motor1 = 0.0;
    motor2 = 0.0;
    motor3 = 0.0;
    motor4 = 0.0;

    //Fim do Programa
    while(true){

    }
}
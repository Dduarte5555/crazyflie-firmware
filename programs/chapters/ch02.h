#include "mbed.h"
#include "crazyflie.h"

// Define o motor como saída PWM
PwmOut motor1(MOTOR1);

// Converte velocidade angular (rad/s) em sinal PWM (%)
float control_motor(float omega){
    float result = (1.4*pow(10, -7) * omega);
    return result;
}

// Main Program
int main(){

    // Frequência PWM para 500Hz
    motor1.period(1.0/500.0);

    // Liga o motor com velocidade angular de 1000 rad/s por 0.5 seg
    motor1 = control_motor(1000.0);
    wait(0.5);

    // Desliga o motor
    motor1 = 0.0;

    //Fim do Programa
    while(true){

    }
}
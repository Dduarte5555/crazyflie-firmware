#include "mbed.h"
#include "crazyflie.h"
#include <cmath>

// Define o motor como saída PWM
PwmOut motor1(MOTOR1);
PwmOut motor2(MOTOR2);
PwmOut motor3(MOTOR3);
PwmOut motor4(MOTOR4);

//Definir velocidades angulares
float omega1;
float omega2;
float omega3;
float omega4;

// Converte velocidade angular (rad/s) em sinal PWM (%)
inline float control_motor(float omega){
    float result = a2*omega*omega;
    return result;
}

void mixer(float f_t, float tau_phi, float tau_theta, float tau_psi){

    omega1 = (1/(4*kl))*f_t - (1/(4*kl*l))*tau_phi - (1/(4*kl*l))*tau_theta - (1/(4*kd))*tau_psi;
    omega2 = (1/(4*kl))*f_t - (1/(4*kl*l))*tau_phi + (1/(4*kl*l))*tau_theta + (1/(4*kd))*tau_psi;
    omega3 = (1/(4*kl))*f_t + (1/(4*kl*l))*tau_phi + (1/(4*kl*l))*tau_theta - (1/(4*kd))*tau_psi;
    omega4 = (1/(4*kl))*f_t + (1/(4*kl*l))*tau_phi - (1/(4*kl*l))*tau_theta + (1/(4*kd))*tau_psi;

    //omega1
    if(omega1 < 0){
        omega1 = 0.0;
    }
    else{
        omega1 = sqrt(omega1);
    }

    //omega2
    if(omega2 < 0){
        omega2 = 0.0;
    }
    else{
        omega2 = sqrt(omega2);
    }

    //omega3
    if(omega3 < 0){
        omega3 = 0.0;
    }
    else{
        omega3 = sqrt(omega3);
    }

    //omega4
    if(omega4 < 0){
        omega4 = 0.0;
    }
    else{
        omega4= sqrt(omega4);
    }

}

void actuate(float f_t, float tau_phi, float tau_theta, float tau_psi){

    mixer(f_t, tau_phi, tau_theta, tau_psi);

    // Liga o motor com velocidade angular de omega_x rad/s
    motor1 = control_motor(omega1);
    motor2 = control_motor(omega2);
    motor3 = control_motor(omega3);
    motor4 = control_motor(omega4);
    
}

// Main Program
int main(){

    // Frequência PWM para 500Hz
    wait(2);
    motor1.period(1.0/500.0);
    motor2.period(1.0/500.0);
    motor3.period(1.0/500.0);
    motor4.period(1.0/500.0);

    actuate(0, 0, 0, -0.001);
    wait(5);

    // Desliga o motor
    actuate(0,0,0,0);

    //Fim do Programa
    while(true){

    }
}
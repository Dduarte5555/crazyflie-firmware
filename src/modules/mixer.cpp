# include "mixer.h"

// Class constructor
Mixer::Mixer() : motor_1(MOTOR1), motor_2(MOTOR2), motor_3(MOTOR3), motor_4(MOTOR4){
    motor_1.period (1.0/500.0) ;
    motor_2.period (1.0/500.0) ;
    motor_3.period (1.0/500.0) ;
    motor_4.period (1.0/500.0) ;
    motor_1 = 0.0;
    motor_2 = 0.0;
    motor_3 = 0.0;
    motor_4 = 0.0;
}

// Actuate motors with desired total trust force (N) and torques (N.m)
void Mixer::actuate (float f_t, float tau_phi, float tau_theta, float tau_psi){
    mixer (f_t, tau_phi, tau_theta, tau_psi );
    motor_1 = control_motor ( omega_1 ) ;
    motor_2 = control_motor ( omega_2 ) ;
    motor_3 = control_motor ( omega_3 ) ;
    motor_4 = control_motor ( omega_4 ) ;

}

// Convert total trust force (N) and torques (N.m) to angular velocities ( rad /s)
void Mixer::mixer(float f_t, float tau_phi, float tau_theta, float tau_psi){

    omega_1 = (1/(4*kl))*f_t - (1/(4*kl*l))*tau_phi - (1/(4*kl*l))*tau_theta - (1/(4*kd))*tau_psi;
    omega_2 = (1/(4*kl))*f_t - (1/(4*kl*l))*tau_phi + (1/(4*kl*l))*tau_theta + (1/(4*kd))*tau_psi;
    omega_3 = (1/(4*kl))*f_t + (1/(4*kl*l))*tau_phi + (1/(4*kl*l))*tau_theta - (1/(4*kd))*tau_psi;
    omega_4 = (1/(4*kl))*f_t + (1/(4*kl*l))*tau_phi - (1/(4*kl*l))*tau_theta + (1/(4*kd))*tau_psi;

    //omega1
    if(omega_1 < 0){
        omega_1 = 0.0;
    }
    else{
        omega_1 = sqrt(omega_1);
    }

    //omega2
    if(omega_2 < 0){
        omega_2 = 0.0;
    }
    else{
        omega_2 = sqrt(omega_2);
    }

    //omega3
    if(omega_3 < 0){
        omega_3 = 0.0;
    }
    else{
        omega_3 = sqrt(omega_3);
    }

    //omega4
    if(omega_4 < 0){
        omega_4 = 0.0;
    }
    else{
        omega_4= sqrt(omega_4);
    }

}

// Convert desired angular velocity ( rad /s) to PWM signal (%)
float Mixer::control_motor(float omega){
    float result = a2*omega*omega;
    return result;
}
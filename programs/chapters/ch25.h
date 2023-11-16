#include "mbed.h"
#include "crazyflie.h"
#include "modules/attitude_estimator.h"
#include "modules/attitude_controller.h"
#include "modules/vertical_estimator.h"
#include "modules/vertical_controller.h"
#include "modules/horizontal_estimator.h"
#include "modules/horizontal_controller.h"

// Crazyflie controller objects
Mixer mixer;
AttitudeEstimator att_est;
AttitudeController att_cont;
VerticalEstimator ver_est;
VerticalController ver_cont;
HorizontalEstimator hor_est;
HorizontalController hor_cont;

// Ticker objects
Ticker tic, tic_range;

// Interrupt flag and counter variables
bool flag, flag_range ;

// Callback functions
void callback(){flag = true;}
void callback_range(){flag_range = true;}

Timer tim;
float tempo;

// Main program
int main()
{
    // Set references
    float z_r = 0.0;
    float x_r = 0.0;
    float y_r = 0.0;
    float psi_r = 0.0;

    float h = 1.0;
    float d = 2.20;
    float tempo_decolagem = 1.8;
    float tempo_voo = 5.0;
    float tempo_pouso = 2.2;

    // Initialize estimators objects
    wait(1); 
    att_est.init();
    ver_est.init();
    hor_est.init();
    // Initialize interrupts
    tic.attach(&callback, dt);
    tic_range.attach(&callback_range, dt_range);
    // Arm motors and run controller while stable
    mixer.arm();
    tim.start();
    tempo = tim.read();

    // TODO:  AUMENTAR TEMPO DE DECOLAGEM 

    while(abs(att_est.phi) <= pi/4.0 && abs(att_est.theta) <= pi/4.0 && abs(att_est.p) <= 4.0*pi && abs(att_est.q) <= 4.0*pi && abs(att_est.r) <= 4.0*pi && tempo < 10)
    {

        if (flag)
        {
            flag = false;
            tempo = tim.read();

            if(tempo < tempo_decolagem)
            {
                z_r = (h/tempo_decolagem) * tempo;
                x_r = 0;
            }

            else if(tempo < tempo_decolagem + tempo_voo)
            {
                z_r = h;
                x_r = (d/tempo_voo)*tempo - (d/tempo_voo)*tempo_decolagem;
            }

            else if(tempo < tempo_decolagem + tempo_voo + tempo_pouso + 1.0)
            {
                z_r = -(h/tempo_pouso) * tempo + (h/tempo_pouso) * (tempo_decolagem + tempo_voo + tempo_pouso);
                x_r = d;
            }

            else{
                z_r=0;
                x_r=d;
            }

            att_est.estimate();
            ver_est.predict(ver_cont.f_t);

            if (flag_range)
            {
                flag_range = false;
                ver_est.correct(att_est.phi, att_est.theta);
            }

            hor_est.predict(att_est.phi, att_est.theta);
            if(ver_est.z >= 0.05)
            {
                hor_est.correct(att_est.phi, att_est.theta, att_est.p, att_est.q, ver_est.z);
                hor_cont.control(x_r, y_r, hor_est.x, hor_est.y, hor_est.u, hor_est.v);
            }

            ver_cont.control(z_r, ver_est.z, ver_est.w);
            att_cont.control(hor_cont.phi_r, hor_cont.theta_r, psi_r, att_est.phi, att_est.theta, att_est.psi, att_est.p, att_est.q, att_est.r);
            mixer.actuate(ver_cont.f_t / (cos(att_est.phi) * cos(att_est.theta)), att_cont.tau_phi, att_cont.tau_theta, att_cont.tau_psi);
        }
    }
    // Disarm motors and end program
    mixer.disarm();
    while (true);
}
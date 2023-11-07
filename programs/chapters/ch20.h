#include "mbed.h"
#include "crazyflie.h"
#include "modules/attitude_estimator.h"
#include "modules/vertical_estimator.h"
#include "modules/attitude_controller.h"
#include "modules/vertical_controller.h"

// Crazyflie controller objects
Mixer mixer;
AttitudeEstimator att_est;
AttitudeController att_cont;
VerticalEstimator ver_est;
VerticalController ver_cont;

// Ticker objects
Ticker tic, tic_range;

// Interrupt flag and counter variables
bool flag, flag_range;

// Callback functions
void callback(){ flag = true; }
void callback_range(){ flag_range = true; }

// Main program
int main()
{
    // Set references
    float z_r = 0.1;
    float phi_r = 0.0;
    float theta_r = 0.0;
    float psi_r = 0.0;
    // Initialize estimators objects
    att_est.init();
    ver_est.init();
    // Initialize interrupts
    tic.attach(&callback, dt);
    tic_range.attach(&callback_range, dt_range);
    // Arm motors and run controller while stable
    mixer.arm();
    while (abs(att_est.phi) <= pi/4.0 && abs(att_est.theta) <= pi/4.0 && abs(att_est.p) <= 4.0 * pi && abs(att_est.q) <= 4.0 * pi && abs(att_est.r) <= 4.0 * pi)
    {
        if (flag)
        {
            flag = false;
            att_est.estimate();
            ver_est.predict(ver_cont.f_t);

            if(flag_range)
            {
                flag_range = false;
                ver_est.correct(att_est.phi, att_est.theta);
            }
            ver_cont.control(z_r, ver_est.z, ver_est.w);
            att_cont.control(phi_r, theta_r, psi_r, att_est.phi, att_est.theta, att_est.psi, att_est.p, att_est.q, att_est.r);

            mixer.actuate(ver_cont.f_t / (cos(att_est.phi) * cos(att_est.theta)), att_cont.tau_phi, att_cont.tau_theta, att_cont.tau_psi);

        }
    }
// Disarm motors and end program
mixer.disarm();
while(true);
}
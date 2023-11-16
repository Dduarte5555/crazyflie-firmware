# include "attitude_estimator.h"
#include <cmath>
#include "pin_names.h"

// Class constructor
AttitudeEstimator :: AttitudeEstimator () : imu ( IMU_SDA , IMU_SCL ), ledRR(LED_RED_R,!false), ledRL(LED_RED_L,!false)
{
    phi, theta, psi = 0;
    p, p_bias, q, q_bias, r, r_bias = 0;
}

// Initialize class
void AttitudeEstimator :: init ()
{
    imu.init();
    float somap, somaq, somar;
    ledRL = !ledRL;
    ledRR = !ledRR;

    for(int i = 0; i<500; i++){
        imu.read();
        somap += imu.gx;
        somaq += imu.gy;
        somar += imu.gz;
        wait(dt);
    }

    ledRL = !ledRL;
    ledRR = !ledRR;
    p_bias = somap/500;
    q_bias = somaq/500;
    r_bias = somar/500;
}

// Estimate Euler angles (rad ) and angular velocities ( rad /s)
void AttitudeEstimator :: estimate ()
{
    imu.read();
    p = imu.gx - p_bias;
    q = imu.gy - q_bias;
    r = imu.gz - r_bias;

    float phi_g = phi + (p + sin(phi) * tan(theta) * q + cos(phi) * tan(theta) * r) * dt;
    float phi_a = atan2(-imu.ay, -imu.az);

    float theta_g = theta + (cos(phi) * q - sin(phi) *r) * dt;
    float theta_a = atan2(imu.ax, (-((imu.az>0)-(imu.az<0))*sqrt(pow(imu.az, 2)+pow(imu.ay, 2))));

    float psi_g = psi + (sin(phi)/cos(theta) * q + cos(phi)/cos(theta) * r) * dt;

    phi = (1.0-alpha)*phi_g + alpha * phi_a;
    theta = (1.0-alpha)*theta_g + alpha * theta_a;
    psi = psi_g;
}

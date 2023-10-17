# include "attitude_estimator.h"
#include <cmath>

// Class constructor
AttitudeEstimator :: AttitudeEstimator () : imu ( IMU_SDA , IMU_SCL )
{
    // (...)
}

// Initialize class
void AttitudeEstimator :: init ()
{
    imu.init();
}

// Estimate Euler angles (rad ) and angular velocities ( rad /s)
void AttitudeEstimator :: estimate ()
{
    imu.read();
    float phi_a = atan2(-imu.ay, -imu.az);
    phi = phi_a;
}

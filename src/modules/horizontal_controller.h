#ifndef horizontal_controller_h
#define horizontal_controller_h

#include "mbed.h"
#include "crazyflie.h"

// Horizontal controller class
class HorizontalController
{
    public:
        // Class constructor
        HorizontalController();
        // Control reference roll and pitch angles (rad) given reference horizontalpositions (m) and current horizontal positions (m) and velocities (m/s)
        void control(float x_r, float y_r, float x, float y, float u, float v);
        // Reference roll and pitch angles (rad)
        float phi_r, theta_r;
        
    private:
        // Control acceleration given reference position (m) and current position (m) and velocity (m/s) with given controller gains
        float control_siso(float position_r, float position, float velocity, float kp, float kd);
};

#endif
#ifndef horizontal_estimator_h
#define horizontal_estimator_h

#include "mbed.h"
#include "crazyflie.h"

// Horizontal estimator class
class HorizontalEstimator
{
    public:
        // Class constructor
        HorizontalEstimator();
        // Initialize class
        void init();
        // Predict horizontal positions and velocities from model
        void predict(float phi, float theta);
        // Correct horizontal velocities with measurements
        void correct(float phi, float theta, float p, float q, float z);
        // Horizontal positions (m) and velocities (m/s) estimations
        float x, y, u, v;
    private:
        // Flow sensor object
        PMW3901 flow;
};

#endif
#include "horizontal_estimator.h"

// Class constructor
HorizontalEstimator::HorizontalEstimator() : flow(PA_7, PA_6, PA_5, PB_4)
{
    x = 0;
    y = 0; 
    u = 0;
    v = 0;
}

// Initialize class
void HorizontalEstimator::init()
{
    flow.init();
}

// Predict horizontal positions and velocities from model
void HorizontalEstimator::predict(float phi, float theta)
{
    x = x + u * dt;
    y = y + v * dt;
    u = u + g * theta * dt;
    v = v - g * phi * dt;
}

// Correct horizontal velocities with measurements
void HorizontalEstimator::correct(float phi, float theta, float p, float q, float z)
{
    float den = cos(phi) * cos(theta);
    if (den > 0.5)
    {
        float d = z/den;
        flow.read();
        float u_m = (sigma_horizontal * flow.px + q) * d;
        float v_m = (sigma_horizontal * flow.py - p) * d;
        u = u + l_horizontal * dt * (u_m - u);
        v = v + l_horizontal * dt * (v_m - v);
    }
}
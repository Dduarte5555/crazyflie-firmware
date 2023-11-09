#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"
#include "modules/attitude_estimator.h"
#include "modules/vertical_estimator.h"
#include "modules/horizontal_estimator.h"

// USB serial object
USBSerial serial;

// Crazyflie controller objects
AttitudeEstimator att_est;
VerticalEstimator ver_est;
HorizontalEstimator hor_est;

// Tickers
Ticker tic , tic_range;

// Interrupt flags
bool flag, flag_range;

// Callback function
void callback(){flag = true;}
void callback_range(){flag_range = true;}

int main()
{
    // Initialize estimators objects
    att_est.init();
    ver_est.init();
    hor_est.init();
    // Initialize interrupts
    tic.attach(&callback, dt);
    tic_range.attach(&callback_range, dt_range );
    while (true)
    {
        if(flag)
        {
            flag = false;
            att_est.estimate();
            ver_est.predict(0.0);
            if (flag_range)
            {
                flag_range = false;
                ver_est.correct (att_est.phi, att_est.theta);
                serial.printf ("x [m]:%6.2f | y [m]:%6.2f | u [m/s]:%6.2f | v [m/s]:%6.2f \n", hor_est.x, hor_est.y, hor_est.u, hor_est.v);
            }
            hor_est.predict(0.0, 0.0);
            if (ver_est.z >= 0.05)
            {
                hor_est.correct(att_est.phi, att_est.theta, att_est.p, att_est.q, ver_est.z);
            }
        }
    }
}
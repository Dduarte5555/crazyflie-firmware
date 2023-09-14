#include "mbed.h"
#include "crazyflie.h"

// Declare mixer
Mixer mixer;

// Main program
int main(){
    
    //Inicialização de 2 segundos
    wait(2);
    
    // Actuate motor with 50% mg total thrust force (N) and zero torques
    mixer.actuate(0, 0, 0, 0);
    wait(5);
    
    // Turn off all motors
    mixer.actuate(0, 0, 0, 0);
    
    // End of program
    while(true){
    }
}
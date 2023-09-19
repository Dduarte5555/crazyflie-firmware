#ifndef parameters_h
#define parameters_h

#include <cmath>

// Physical constants
const float pi = 3.1416;
const float g = 9.81;       // m/s^2

// Quadcopter dimensions
const float m = 30.0e-3;    // kg
const float I_xx = 16.0e-6; // kg.m^2
const float I_yy = 16.0e-6; // kg.m^2
const float I_zz = 29.0e-6; // kg.m^2
const float l = 33.0e-3;    // m

const float a2 = 1.4e-7;
const float kl = 1.7e-8;
const float kd = 1.012e-10;

const int la = 440; //La
const int d = 524; //Do (como mencionado anteriormente, 523.25 Hz é a frequência padrão, mas estou dobrando o valor que você forneceu)
const int r = 588; //Re
const int mi = 660; //Mi
const int f = 696; //Fa
const int s = 784; //Sol
const int laa = 880; //La
const int lS = 932; //La#
const int si = 988; //si
const int Do = 1048; //do
const int Re = 1176; //re
const int Mi = 1316; //Mi
const int Fa = 1396; //Fa
const int Sol = 1568; //Sol
const int La = 1760; //La
const int LaS = 1864; //La#
const int Si = 1976; //si
const int Doo = 2092; //do




#endif
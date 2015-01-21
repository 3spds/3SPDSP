/*
CGain.cpp - implement 2-pole / zero filter sections using complex numbers
jm
*/

#include "./cgain.h"

using namespace std;

TwoPoleReal::TwoPoleReal()
{
    TwoPoleReal::init();
}

TwoPoleReal::~TwoPoleReal()
{
}

void TwoPoleReal::init()
{
    setCoefs(0.0, 0.0);
    fbBuf = polar(0.0, 0.0);
}

void TwoPoleReal::setCoefs(double pRho, double pTheta)
{
    theta = pTheta;
    rho = pRho;
    fbCoef = polar(rho, theta);
}

void TwoPoleReal::setTheta(double pTheta)
{
    theta = pTheta;
    fbCoef = polar(rho, theta);
}

void TwoPoleReal::setRho(double pRho)
{
    rho = pRho;
    fbCoef = polar(rho, theta);
}

double TwoPoleReal::getTheta()
{
    return this->theta;
}

double TwoPoleReal::getRho()
{
    return this->rho;
}

void TwoPoleReal::apply(float* signal)
{
    complex<double> dsignal(*signal, 0.0);
    fbBuf *= fbCoef;
    fbBuf += dsignal;
    *signal = (float) real(fbBuf);
}



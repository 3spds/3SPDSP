/*
CGain.cpp - implement 2-pole / zero filter sections using complex numbers
jm
*/

#include "./cgain.h"

using namespace std;

//--- TwoPoleReal

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


//----TwoZeroReal

TwoZeroReal::TwoZeroReal()
{
    TwoZeroReal::init();
}

TwoZeroReal::~TwoZeroReal()
{
}

void TwoZeroReal::init()
{
    setCoefs(0.0, 0.0);
    ffBuf = polar(0.0, 0.0);
}

void TwoZeroReal::setCoefs(double pRho, double pTheta)
{
    theta = pTheta;
    rho = pRho;
    ffCoef = polar(rho, theta);
}

void TwoZeroReal::setTheta(double pTheta)
{
    theta = pTheta;
    ffCoef = polar(rho, theta);
}

void TwoZeroReal::setRho(double pRho)
{
    rho = pRho;
    ffCoef = polar(rho, theta);
}

double TwoZeroReal::getTheta()
{
    return this->theta;
}

double TwoZeroReal::getRho()
{
    return this->rho;
}

void TwoZeroReal::apply(float* signal)
{
    complex<double> dsignal(*signal, 0.0);
    *signal = (float) real(dsignal + ffBuf);
    ffBuf = *signal;
    ffBuf *= ffCoef;
}

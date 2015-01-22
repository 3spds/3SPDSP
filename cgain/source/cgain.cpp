/*
CGain.cpp - implement 2-pole / zero filter sections using complex numbers
jm
*/

#include "./cgain.h"

using namespace std;

//--- OnePoleComplex

OnePoleComplex::OnePoleComplex()
{
    OnePoleComplex::init();
}

OnePoleComplex::~OnePoleComplex()
{
}

void OnePoleComplex::init()
{
    setCoefs(0.0, 0.0);
    fbBuf = polar(0.0, 0.0);
}

void OnePoleComplex::setCoefs(double pRho, double pTheta)
{
    theta = pTheta;
    rho = pRho;
    fbCoef = polar(rho, theta);
}

void OnePoleComplex::setTheta(double pTheta)
{
    theta = pTheta;
    fbCoef = polar(rho, theta);
}

void OnePoleComplex::setRho(double pRho)
{
    rho = pRho;
    fbCoef = polar(rho, theta);
}

double OnePoleComplex::getTheta()
{
    return this->theta;
}

double OnePoleComplex::getRho()
{
    return this->rho;
}

void OnePoleComplex::apply(complex<double>* signal)
{
    complex<double> dsignal = *signal;
    fbBuf *= fbCoef;
    fbBuf += dsignal;
    *signal = fbBuf;
}


//----OneZeroComplex

OneZeroComplex::OneZeroComplex()
{
    OneZeroComplex::init();
}

OneZeroComplex::~OneZeroComplex()
{
}

void OneZeroComplex::init()
{
    setCoefs(0.0, 0.0);
    ffBuf = polar(0.0, 0.0);
}

void OneZeroComplex::setCoefs(double pRho, double pTheta)
{
    theta = pTheta;
    rho = pRho;
    ffCoef = polar(rho, theta);
}

void OneZeroComplex::setTheta(double pTheta)
{
    theta = pTheta;
    ffCoef = polar(rho, theta);
}

void OneZeroComplex::setRho(double pRho)
{
    rho = pRho;
    ffCoef = polar(rho, theta);
}

double OneZeroComplex::getTheta()
{
    return this->theta;
}

double OneZeroComplex::getRho()
{
    return this->rho;
}

void OneZeroComplex::apply(complex<double>* signal)
{
    complex<double> dsignal = *signal;
    *signal = dsignal - ffBuf;
    ffBuf = dsignal;
    ffBuf *= conj(ffCoef);
}

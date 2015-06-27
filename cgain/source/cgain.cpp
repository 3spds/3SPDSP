/*
CGain.cpp - implement 2-pole / zero filter sections using complex numbers
jm
*/

#include "./cgain.h"

using namespace std;

//--- OneStageComplex

OneStageComplex::OneStageComplex()
{
    OneStageComplex::init();
}

OneStageComplex::~OneStageComplex()
{
}

void OneStageComplex::init()
{
    setCoefsPolar(0.0, 0.0);
    buf = polar(0.0, 0.0);
}

void OneStageComplex::setCoefsPolar(double pRho, double pTheta)
{
    theta = pTheta;
    rho = pRho;
    coef = polar(rho, theta);
}

void OneStageComplex::setCoefsCart(double x, double y)
{
    coef = complex<double>(x, y);
}

void OneStageComplex::setTheta(double pTheta)
{
    theta = pTheta;
    coef = polar(rho, theta);
}

void OneStageComplex::setRho(double pRho)
{
    rho = pRho;
    coef = polar(rho, theta);
}

double OneStageComplex::getTheta()
{
    return this->theta;
}

double OneStageComplex::getRho()
{
    return this->rho;
}

complex<double> OneStageComplex::getCoef()
{
    return this->coef;
}

double OneStageComplex::getReal()
{
    return this->coef.real();
}

double OneStageComplex::getImag()
{
    return this->coef.imag();
}

std::complex<double> OneStageComplex::getBuf()
{
    return this->buf;
}

void OneStageComplex::setBuf(std::complex<double> pBuf)
{
    this->buf = pBuf;
}

//--- OnePoleComplex

OnePoleComplex::OnePoleComplex() : OneStageComplex()
{
    OnePoleComplex::init();
}

OnePoleComplex::~OnePoleComplex()
{
}

void OnePoleComplex::apply(complex<double>* signal)
{
    complex<double> dsignal = *signal;
    setBuf(getBuf() *= getCoef());
    setBuf(getBuf() + dsignal);
    *signal = getBuf();
}


//----OneZeroComplex

OneZeroComplex::OneZeroComplex() : OneStageComplex()
{
    OneZeroComplex::init();
}

OneZeroComplex::~OneZeroComplex()
{
}

void OneZeroComplex::apply(complex<double>* signal)
{
    complex<double> dsignal = *signal;
    *signal = dsignal + getBuf();
    setBuf(dsignal);
    setBuf(getBuf() * getCoef());
}

//----TwoPoleComplex

TwoPoleComplex::TwoPoleComplex()
{
    TwoPoleComplex::init();
}

TwoPoleComplex::~TwoPoleComplex()
{
}

void TwoPoleComplex::init()
{
    for(int i=0; i<2; i++)
    {
        this->poles[i].init();
    }
}

void TwoPoleComplex::setAllCoefsPolar(double pRho, double pTheta)
{
    this->setAllRho(pRho);
    this->setAllTheta(pTheta);
}

void TwoPoleComplex::setAllTheta(double pTheta)
{
    setTheta(pTheta);
    this->poles[0].setTheta(pTheta);
    this->poles[1].setTheta(-pTheta);
}

void TwoPoleComplex::setAllRho(double pRho)
{
    setRho(pRho);
    this->poles[0].setRho(pRho);
    this->poles[1].setRho(pRho);
}


void TwoPoleComplex::apply(complex<double>* signal)
{
//    complex<double> dsignal = *signal;
//    this->poles[0].apply(&dsignal);
//    this->poles[1].apply(signal);
//    *signal+= dsignal;
//    *signal*=0.5;
    this->poles[0].apply(signal);
    this->poles[1].apply(signal);
}


//----TwoZeroComplex

TwoZeroComplex::TwoZeroComplex()
{
    TwoZeroComplex::init();
}

TwoZeroComplex::~TwoZeroComplex()
{
}

void TwoZeroComplex::init()
{
    for(int i=0; i<2; i++)
    {
        this->zeros[i].init();
    }
}

void TwoZeroComplex::setAllCoefsPolar(double pRho, double pTheta)
{
    setAllRho(pRho);
    setAllTheta(pTheta);
}

void TwoZeroComplex::setAllTheta(double pTheta)
{
    setTheta(pTheta);
    this->zeros[0].setTheta(pTheta);
    this->zeros[1].setTheta(-pTheta);
}

void TwoZeroComplex::setAllRho(double pRho)
{
    setRho(pRho);
    this->zeros[0].setRho(pRho);
    this->zeros[1].setRho(pRho);
}

void TwoZeroComplex::apply(complex<double>* signal)
{
    //complex<double> dsignal = *signal;
    //this->zeros[0].apply(&dsignal);
    //this->zeros[1].apply(signal);
    //*signal+= dsignal;
    //*signal*=0.5;
    this->zeros[0].apply(signal);
    this->zeros[1].apply(signal);

}


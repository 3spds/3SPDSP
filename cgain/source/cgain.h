/*
CGain.h - implement 2-pole / zero filter sections using complex numbers
jm
*/

#include <complex>
#include <cmath>
#include <iostream>

class OneStageComplex
{
    std::complex<double>buf;
    std::complex<double>coef;
    double theta;
    double rho;
public:
    OneStageComplex();
    ~OneStageComplex();
    void init();
    void setCoefsPolar(double pRho, double pTheta);
    void setCoefsCart(double x, double y);
    std::complex<double> getCoef();
    std::complex<double> getBuf();
    void setBuf(std::complex<double> pBuf);
    double getReal();
    double getImag();
    double getTheta();
    double getRho();
    void setTheta(double pTheta);
    void setRho(double pRho);
};

class OnePoleComplex : public OneStageComplex
{
    std::complex<double> buf;
    std::complex<double> coef;
    double theta;
    double rho;
public:
    OnePoleComplex();
    ~OnePoleComplex();
    void apply(std::complex<double>* signal);
};

class OneZeroComplex : public OneStageComplex
{
    std::complex<double> buf;
    std::complex<double> coef;
    double theta;
    double rho;
public:
    OneZeroComplex();
    ~OneZeroComplex();
    void apply(std::complex<double>* signal);
};

class TwoPoleComplex : public OneStageComplex
{
    OnePoleComplex poles[2];
    double theta;
    double rho;
public:
    TwoPoleComplex();
    ~TwoPoleComplex();
    void init();
    void setAllCoefsPolar(double pRho, double pTheta);
    void setAllTheta(double pTheta);
    void setAllRho(double pRho);
    void apply(std::complex<double>* signal);
};

class TwoZeroComplex : public OneStageComplex
{
    OneZeroComplex zeros[2];
    double theta;
    double rho;
public:
    TwoZeroComplex();
    ~TwoZeroComplex();
    void init();
    void setAllCoefsPolar(double pRho, double pTheta);
    void setAllTheta(double pTheta);
    void setAllRho(double pRho);
    void apply(std::complex<double>* signal);
};

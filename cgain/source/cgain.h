/*
CGain.h - implement 2-pole / zero filter sections using complex numbers
jm
*/

#include <complex>
#include <cmath>

class OnePoleComplex
{
    std::complex<double> fbBuf;
    std::complex<double> fbCoef;
    double theta;
    double rho;
public:
    OnePoleComplex();
    ~OnePoleComplex();
    void init();
    void setCoefs(double pRho, double pTheta);
    double getTheta();
    double getRho();
    void setTheta(double pTheta);
    void setRho(double pRho);
    void apply(std::complex<double>* signal);
};

class OneZeroComplex
{
    std::complex<double> ffBuf;
    std::complex<double> ffCoef;
    double theta;
    double rho;
public:
    OneZeroComplex();
    ~OneZeroComplex();
    void init();
    void setCoefs(double pRho, double pTheta);
    double getTheta();
    double getRho();
    void setTheta(double pTheta);
    void setRho(double pRho);
    void apply(std::complex<double>* signal);
};

class TwoPoleComplex
{
    OnePoleComplex poles[2];
    double theta;
    double rho;
public:
    TwoPoleComplex();
    ~TwoPoleComplex();
    void init();
    void setCoefs(double pRho, double pTheta);
    double getTheta();
    double getRho();
    void setTheta(double pTheta);
    void setRho(double pRho);
    void apply(std::complex<double>* signal);
};

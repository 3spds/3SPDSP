/*
CGain.h - implement 2-pole / zero filter sections using complex numbers
jm
*/

#include <complex>
#include <cmath>

class TwoPoleReal
{
    std::complex<double> fbBuf;
    std::complex<double> fbCoef;
    double theta;
    double rho;
public:
    TwoPoleReal();
    ~TwoPoleReal();
    void init();
    void setCoefs(double pRho, double pTheta);
    double getTheta();
    double getRho();
    void setTheta(double pTheta);
    void setRho(double pRho);
    void apply(float* signal);
};

class TwoZeroReal
{
    std::complex<double> ffBuf;
    std::complex<double> ffCoef;
    double theta;
    double rho;
public:
    TwoZeroReal();
    ~TwoZeroReal();
    void init();
    void setCoefs(double pRho, double pTheta);
    double getTheta();
    double getRho();
    void setTheta(double pTheta);
    void setRho(double pRho);
    void apply(float* signal);
};

/*
main.cpp - implement 2-pole / zero filter sections using complex numbers
jm
*/

#include "./cgain.cpp"
#include <cmath>
#include <iostream>

#define LENGTH 100

using namespace std;

int main()
{
    int reps = LENGTH;
    complex<double> impulse[LENGTH];
    for(int i = 0; i < LENGTH; i++)
    {
        impulse[i] = complex<double>(0.0, 0.0);
    }
    impulse[0] = complex<double>(0.707, 0.707);
    complex<double> signal = 0.0;
    complex<double> out = 0.0;
    OnePoleComplex* filter = new OnePoleComplex;
    OneZeroComplex* filter0 = new OneZeroComplex;
    filter->init();
    filter0->init();
    filter->setCoefs(1.0, (double)(M_PI/8));
    filter0->setCoefs(1.0, (double)(-M_PI/8));
    while(reps--)
    {
        signal = impulse[LENGTH-1-reps];
        filter->apply(&signal);
        filter0->apply(&signal);
        out = signal;
        cout<<out<<endl;
    }
    return 0;
}

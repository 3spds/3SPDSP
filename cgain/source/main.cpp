/*
main.cpp - implement 2-pole / zero filter sections using complex numbers
jm
*/

#include "./cgain.h"
#include <cmath>
#include <iostream>

#define LENGTH 10

using namespace std;

int main()
{
    int reps = LENGTH;
    complex<double> impulse[LENGTH];
    for(int i = 0; i < LENGTH; i++)
    {
        impulse[i] = complex<double>(0.0, 0.0);
    }
    impulse[0] = complex<double>(0.707, 0.0);
    cout<<"-----One Pole -> One Zero Cancellation-----"<<endl;
    complex<double> signal = 0.0;
    complex<double> out = 0.0;
    OnePoleComplex filter;
    OneZeroComplex filter0;
    filter.setCoefsPolar(1, (double)(M_PI/2));
    filter0.setCoefsPolar(1, -(double)(M_PI/2));
    while(reps--)
    {
        signal = impulse[LENGTH-1-reps];
        filter.apply(&signal);
        cout<<"pole: "<<signal<<endl;
        filter0.apply(&signal);
        out = signal;
        cout<<"zero: "<< out<<endl;
    }

    cout<<"-----Two Pole -> Two Zero 'Cancellation'-----"<<endl;
    reps = LENGTH;
    signal = 0.0;
    out = 0.0;
    TwoPoleComplex filter1;
    TwoZeroComplex filter2;
    filter1.setAllCoefsPolar(0.5, (double)(M_PI/2));
    filter2.setAllCoefsPolar(0.5, (double)(M_PI/2));

    while(reps--)
    {
        signal = impulse[LENGTH-1-reps];
        filter1.apply(&signal);
        cout<<"pole: "<<signal<<endl;
        filter2.apply(&signal);
        out = signal;
        cout<<"zero: "<< out<<endl;
    }
    return 0;
}

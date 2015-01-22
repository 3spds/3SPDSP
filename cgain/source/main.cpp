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
    float impulse[LENGTH];
    for(int i = 0; i < LENGTH; i++)
    {
        impulse[i] = 0.0f;
    }
    impulse[0] = 1.0f;
    float signal = 0.0;
    float out = 0.0;
    TwoPoleReal* filter = new TwoPoleReal;
    TwoZeroReal* filter0 = new TwoZeroReal;
    filter->init();
    filter0->init();
    filter->setCoefs(1, (double)(M_PI/8));
    filter0->setCoefs(1, (double)(M_PI/8));
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

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
    filter->init();
    filter->setCoefs(1, (double)(M_PI/2));
    while(reps--)
    {
        signal = impulse[LENGTH-1-reps];
        filter->apply(&signal);
        cout<<signal<<endl;
    }
    return 0;
}

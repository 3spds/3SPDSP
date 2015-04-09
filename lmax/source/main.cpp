/*
main.cpp - implement local maximum search
jm
*/
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

void localMax(int* input, int* output, int nSamps, int k)
{
    for(int i = 0; i < nSamps;)
    {
        for(int j = 1; j <= k;)
        {
            if(input[i] > input[(i+j)%nSamps]) //bigger than neighbor
            {
                j++;
                if(j > k) //neighborhood exhausted
                {
                    output[i] = 1;
                    i += k;
                }
            }
            else //smaller than neighbor
            {
                i += j;
                break;
            }
        }
    }
}

void randArray(int* vec, int length){
    srand(time(NULL));
    for(int i=0; i<length; i++){
        vec[i] = rand() % 10;
    }
}

void printArray(int* vec, int length){
    for(int i=0; i<length; i++){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}

void zeroArray(int* vec, int length)
{
    for(int i=0; i<length; i++)
    {
        vec[i] = 0;
    }
}

int main()
{
    int length;
    cout<<"length of sequence:";
    cin>>length;
    int* input = new int[length]();
    int* output = new int[length]();
    randArray(input, length);
    printArray(input, length);
    zeroArray(output, length);
    int k = 1;
    cout<<"find local maxima in neighborhood of size (0: exit):";
    cin>>k;
    while(k > 0)
    {
        zeroArray(output, length);
        localMax(input, output, length, k);
        printArray(output, length);
        cout<<"next neigbhorhood size:";
        cin>>k;
    }
    delete[] input;
    delete[] output;
    return 0;
}

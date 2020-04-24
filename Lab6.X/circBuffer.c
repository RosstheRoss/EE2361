#include "xc.h"
#include "circBuffer.h"
#define SIZE 1024

volatile unsigned long buffer[SIZE];
int buffSize = 0;
void initBuffer(){
    int i;
    for (i=0; i<SIZE; i++) {
        buffer[i]=0;
    }
    buffSize = 0;
}

void putVal(long newValue){
    buffer[buffSize++] = newValue;
    if (buffSize > SIZE)
        buffSize = 0;
}
long getAvg(){
    int i, sum = 0;
    for (i=0; i<SIZE; i++) {
        sum += buffer[i];
    } return sum / SIZE;
}

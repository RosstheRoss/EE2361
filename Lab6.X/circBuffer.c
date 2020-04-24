#include "xc.h"
#include "circBuffer.h"
#define SIZE 1024

volatile unsigned int buffer[SIZE];
int buffSize = 0, write = 0, read = 0;
void initBuffer(){
    int i;
    for (i=0; i<SIZE; i++) {
        buffer[i]=0;
    }
    buffSize = 0, write = 0, read = 0;
}

void putVal(int newValue){
        if (buffSize < SIZE) {
          buffer[write++] = newValue;
          write %= SIZE;
          ++buffSize;
    }
    //Otherwise get rid of the data.
}
int getAvg(){
    int i, sum = 0;
    for (i=0; i<SIZE; i++) {
        sum += buffer[i];
    } return sum / SIZE;
}

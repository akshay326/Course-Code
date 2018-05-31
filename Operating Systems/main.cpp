#include<iostream>
using namespace std;

#define stderr "NDK-BUILD"
#define FPRINTF(a,b,c) printf(b,c)

int main() {
    FPRINTF(stderr,"The number is %d",4);

    return 0;
}
#include<iostream>
#include<cstdio>
#include <bitset>
#include <time.h>
using namespace std;

int makeEqualLength(string &str1, string &str2);
string addBitStrings( string first, string second);
long katasurba(string X, string Y);

#define MAX_VAL 100
int main(){
	
	std::cout<<"Enter 2 numbers to katasurba line by line:"<<std::endl;
	long long a,b;
	std::cin >> a >> b;
	
	clock_t tStart = clock();
	std::cout<< katasurba(std::bitset< 64 >(a).to_string(), std::bitset< 64 >( b).to_string())<<std::endl;
	printf("Time Katasurba cycles\n");
	std::cout<<clock() - tStart;
	
	tStart = clock();
	std::cout<<a*b;
	printf("Time Katasurba cycles\n");
	std::cout<<clock() - tStart;
	
	
	/*
	string a="11111111",b="11111111";
	clock_t tStart;
	
	
	for(int i = 0;i<100;++i){
		tStart = clock();
		a += "111";
		b += "111";
		
		katasurba(a,b);
		printf("Time Katasurba Iteration %d: %.3f ms\n", i+1,(double)(clock() - tStart)*1000/CLOCKS_PER_SEC);
	}
	*/
	
	return 0;
}

int makeEqualLength(string &str1, string &str2){
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            str2 = '0' + str2;
    }
    return len1; // If len1 >= len2
}

// The main function that adds two bit sequences and returns the addition
string addBitStrings( string first, string second ){
    string result;  // To store the sum bits

    // make the lengths same before adding
    int length = makeEqualLength(first, second);
    int carry = 0;  // Initialize carry

    // Add all bits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = first.at(i) - '0';
        int secondBit = second.at(i) - '0';

        // boolean expression for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry)+'0';

        result = (char)sum + result;

        // boolean expression for 3-bit addition
        carry = (firstBit&secondBit) | (secondBit&carry) | (firstBit&carry);
    }

    // if overflow, then add a leading 1
    if (carry)  result = '1' + result;

    return result;
}

long katasurba(string X, string Y){

    int n = makeEqualLength(X, Y);

    // Base cases
    if (n == 0) return 0;
    if (n == 1) return (X[0] - '0')*(Y[0] - '0'); 

    int left = n/2;   // First half of string, floor(n/2)
    int right = (n-left); // Second half of string, ceil(n/2)

    string Xl = X.substr(0, left);
    string Xr = X.substr(left, right);

    // Find the first half and second half of second string
    string Yl = Y.substr(0, left);
    string Yr = Y.substr(left, right);

    // Recursively calculate the three products of inputs of size n/2
    long int P1 = katasurba(Xl, Yl);
    long int P2 = katasurba(Xr, Yr);
    long int P3 = katasurba(addBitStrings(Xl, Xr), addBitStrings(Yl, Yr));

    // Combine the three products
    return P1*(1<<(2*right)) + (P3 - P1 - P2)*(1<<right) + P2;
}

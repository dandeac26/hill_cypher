#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ofstream g("KEYS.txt");

int N = 26; // alphabet size

bool isSquare(int a, int b, int c, int d) {
    return ((a * a + b * c) % N == 1 &&
    (c * b + d * d) % N == 1 &&
    (c * a + d * c) % N == 0 &&
    (a * b + b * d) % N == 0);
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

bool hasInversZ26(int det){
    return gcd(det, N) == 1;
}

bool satisfiesCondition(int a, int b, int c, int d){
    int det = (a*d-b*c)%N < 0 ? 26+(a*d-b*c)%N : (a*d-b*c)%N ;
    return (det != 0) && (gcd(det, N)==1);
}



int main(int argc, char* argv[])
{
    if(argc > 1){
        N = atoi(argv[1]);
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                for(int l=0;l<N;l++){
                    if (satisfiesCondition(i, j, k, l)!=0){
                        g << char(65 + i) << char(65 + j) <<  char(65 + k) << char(65 + l)<< endl;
                    } 
                }
            }
        }
    }
            
}
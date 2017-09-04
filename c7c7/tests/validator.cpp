#include <iostream>
#include <string>
#include "./testlib.h"
#include <cassert>
using namespace std;
#define MIN_N 1
#define MAX_N 1000
#define MIN_M 1
#define MAX_M 30
int main(){

    registerValidation();

    int n = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();

    int m = inf.readInt(MIN_M, MAX_M);
    inf.readEoln();

    for(int i = 0; i < n; i++){
        string s = inf.readString();
        if((int)s.size()!=m)assert(1);
        for(int j=0;j<s.size();j++){
            if(s[j]<'a'||'z'<s[j])assert(1);
        }
    }
    inf.readEof();
}
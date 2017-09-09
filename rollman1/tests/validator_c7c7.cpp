#include <iostream>
#include <string>
#include "./testlib.h"
#include <cassert>
using namespace std;
#define MIN_N 1
#define MAX_N 100000
#define MIN_M 0
#define MAX_M 1000000000
int main(){

    registerValidation();

    int n = inf.readInt(MIN_N, MAX_N);

    inf.readEoln();

    for(int i = 0; i < n; i++){

        int m = inf.readInt(MIN_M, MAX_M);

        inf.readEoln();

    }
    inf.readEof();
}
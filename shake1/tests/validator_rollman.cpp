#include <iostream>
#include <vector>
#include "testlib.h"
using namespace std;
typedef long long ll;

const ll MIN_n = 1;
const ll MAX_n = 1e18;

void input() {
  ll n = inf.readLong(MIN_n, MAX_n, "N");
  inf.readEoln();
  inf.readEof();
}

void check() {
}

int main() {
  registerValidation();
  input();
  check();
  return 0;
}

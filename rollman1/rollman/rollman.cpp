#include <bits/stdc++.h>
using namespace std;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> a;
    a = vector<int>(N);

    for(int i = 0; i < N; i++){
        cin >> a[i];
    }

    int ans = 1;
    int local = 1;
    for(int i = 1; i < N; i++){
      if(a[i] > a[i-1]){
        local++;
        ans = max(ans, local);
      }else if(a[i] == a[i-1]){
      }else{
        local = 1;
      }
    }

    local = 1;
    for(int i = 1; i < N; i++){
      if(a[i] < a[i-1]){
        local++;
        ans = max(ans, local);
      }else if(a[i] == a[i-1]){
      }else{
        local = 1;
      }
    }
    cout << ans << endl;
}

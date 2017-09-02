#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

int N;
vector<int> a;

bool playable(int idx, int prev_fing, const int fing){
    if(idx == N) return true;


    bool res = false;
    if(idx == 0){
        for(int i = 0; i < fing; i++){
            res |= playable(idx+1, i, fing);
        }
    }else{
        int prev_idx = idx-1;
        if(a[idx] == a[prev_idx]){
            res |= playable(idx+1, prev_fing, fing);
        }else if(a[idx] > a[prev_idx]){
            for(int i = prev_fing+1; i < fing; i++){
                res |= playable(idx+1, i, fing);
            }
        }else{ // a[idx] < a[prev_idx]
            for(int i = prev_fing-1; i >= 0; i--){
                res |= playable(idx+1, i, fing);
            }
        }
    }
    return res;
}

int main(void){
    cin >> N;
    a = vector<int>(N);

    for(int i = 0; i < N; i++){
        cin >> a[i];
    }

    int fing;
    for(fing = 1;; fing++){
        if(playable(0, -1, fing)) break;
    }
    cout << fing << endl;
}

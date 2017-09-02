#include <bits/stdc++.h>
using namespace std;

const int TRUE = 1;
const int FALSE = 0;
const int NONE = -1;

const int MAXN = 1000;

int N;
vector<int> a;

int memo[MAXN][MAXN];

int playable(int idx, int prev_fing, const int fing){
    if(prev_fing != -1 && memo[idx][prev_fing] != NONE){
        return memo[idx][prev_fing];
    }
    if(idx == N) return TRUE;


    int res = FALSE;
    if(idx == 0){
        for(int i = 0; i < fing; i++){
            //res |= playable(idx+1, i, fing);
            if(playable(idx+1, i, fing) == TRUE) res = TRUE;
        }
    }else{
        int prev_idx = idx-1;
        if(a[idx] == a[prev_idx]){
            //res |= playable(idx+1, prev_fing, fing);
            if(playable(idx+1, prev_fing, fing) == TRUE) res = TRUE;
        }else if(a[idx] > a[prev_idx]){
            for(int i = prev_fing+1; i < fing; i++){
                //res |= playable(idx+1, i, fing);
                if(playable(idx+1, i, fing) == TRUE) res = TRUE;
            }
        }else{ // a[idx] < a[prev_idx]
            for(int i = prev_fing-1; i >= 0; i--){
                //res |= playable(idx+1, i, fing);
                if(playable(idx+1, i, fing) == TRUE) res = TRUE;
            }
        }
    }
    return memo[idx][prev_fing] = res;
}

int main(void){
    cin >> N;
    a = vector<int>(N);
    for(int i = 0; i < N; i++){
        cin >> a[i];
    }


    int fing;
    for(fing = 1;; fing++){
        for(int i = 0; i < MAXN; i++) for(int j = 0; j < MAXN; j++) memo[i][j] = NONE;
        if(playable(0, -1, fing) == TRUE) break;
    }
    cout << fing << endl;
}

#include <bits/stdc++.h>
using namespace std;

const int UP=1;
const int DOWN=0;
const int EQ=-1;

int main(void){
    int N;
    cin >> N;
    vector<int> a;
    a = vector<int>(N);

    for(int i = 0; i < N; i++){
        cin >> a[i];
    }

    int ans = true;

    for(int i = 0; i < N; i++){
        if(a[0] != a[i]) ans = false;
    }
    if(ans == true){
        cout << "1" << endl;
        return 0;
    }




    ans = 1;
    int local = 1;
    int prev = EQ;
    for(int i = 0; i < N-1; i++){
        if(a[i+1] == a[i]){
            ans = max(ans, local+1);
            local = 1;
            prev = EQ;
        }else if(a[i+1] > a[i]){
            if(prev == UP){
                local++;
            }else{
                ans = max(ans, local+1);
                local = 1;
            }
            prev = UP;
        }else{
            if(prev == DOWN){
                local++;
            }else{
                ans = max(ans, local+1);
                local = 1;
            }
            prev = DOWN;
        }
    }

    cout << ans << endl;
}

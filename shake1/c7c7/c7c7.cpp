#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
main(){
	while(cin>>n,n){
		for(int i=0;(1<<i)<n;i++){
			if(!((1<<i)&n)){
				cout<<i+1<<endl;
				goto L;
			}
		}
		cout<<(-1)<<endl;
		L:;
	}
}
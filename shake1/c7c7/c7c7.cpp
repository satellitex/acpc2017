#include <bits/stdc++.h>
using namespace std;
#define int long long
main{
	while(cin>>n,n){
		for(int i=1;i<n;i*=2){
			if(!((1<<i)&n)){
				cout<<i<<endl;
				goto L;
			}
		}
		cout<<(-1)<<endl;
		L:;
	}
}
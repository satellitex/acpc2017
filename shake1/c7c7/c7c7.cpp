#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
main(){
	cin>>n;
	for(int i=0;(1<<i)<n;i++){
		if(!((1<<i)&n)){
			cout<<(1<<i)<<endl;
			return 0;
		}
	}
	cout<<(-1)<<endl;
}
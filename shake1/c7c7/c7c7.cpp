#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
main(){
	cin>>n;
	for(int i=0;((int)1<<i)<n;i++){
		if(!(((int)1<<i)&n)){
			cout<<((int)1<<i)<<endl;
			return 0;
		}
	}
	cout<<n+1<<endl;
}
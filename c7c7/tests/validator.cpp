#include <bits/stdc++.h>

using namespace std;

int N,M;
string s;
int main() {
	cin>>N>>M;
	if(N<1||1000<N||M<1||30<M)exit(1);
	for(int i=0;i<N;i++){
		cin>>s;
		for(int j=0;j<M;j++){
			if(s[j]<'a'||'z'<s[j])exit(1);
		}
		if(s.size()!=M)exit(1);
	}
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N,M;
string s;
int main() {
	cin>>N>>M;
	if(N<1||1000<N||M<1||30<M)exit(1);
	for(int i=0;i<N;i++){
		cin>>s;
		if(s.size()!=M)exit(1);
	}
}

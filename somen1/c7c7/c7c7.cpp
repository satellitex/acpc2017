#include<iostream>
using namespace std;
int main(){
	int n,x;
	cin>>n;
	while(n--){
		cin>>x;
		cout<<x/30<<' '<<(x%30)*2<<endl;
	}
}
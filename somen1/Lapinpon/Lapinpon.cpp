#include <iostream>
using namespace std;
int main(){

  int n,de;

  cin>>n;
  for(int i=0;i<n;i++){
    cin>>de;
    cout<<de/30<<" "<<de%30*2<<endl;
  }

  return 0;

}

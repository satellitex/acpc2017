#include<bits/stdc++.h>
using namespace std;

string i2s(int i){
  stringstream ss;
  ss<<i;
  string res;
  ss>>res;
  return res;
}

#define LEN 20
std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randA(1,LEN);
std::uniform_int_distribution<> randB(1,10000);

void solve(int ID){

  ofstream fout ( "randMid"+ i2s(ID) +".in" );

  
  fout<<LEN<<endl;
  for(int p=0;p<2;p++){
    for(int i=0;i<LEN;i++){
      if(i)fout<<' ';
      fout<<randB(mt);
    }
    fout<<endl;
  }

  int Q=200000;
  fout<<Q<<endl;
  for(int i=0;i<Q;i++){
    
    if(randB(mt)%10==0){
      fout<< randB(mt)%2+5 <<' '<<-1<<' '<<-1<<endl;
      continue;
    }
    
    int L=randA(mt), R=randA(mt);

    
    if(randB(mt)%2==0){
      fout<<randB(mt)%2+1<<' '<<L<<' '<<randB(mt)+i/10<<endl;
    }else{
      if(L>R)swap(L,R);
      fout<<randB(mt)%2+3<<' '<<L<<' '<<R<<endl;
    }
    
  }

  
  fout.close();
}

int main(){
  for(int i=0;i<5;i++){
    solve(i);
  }
  return 0;
}





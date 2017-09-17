#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
#define MAX 2050

int N;
char t[MAX][MAX];
bool T[MAX][MAX];
int a[MAX][MAX];
int b[MAX][MAX];

map < P , vector<P> > G;

bool inField(int y,int x){
  return (0<=y&&y<N&&0<=x&&x<N);
}

bool inField(P p){
  return inField(p.first,p.second);
}

bool inField(int ay,int ax,int by,int bx,P p){
  int y=p.first;
  int x=p.second;
  return (ay<y&&y<by&&ax<x&&x<bx);
}

map< P , P > mem[4];

P search(P p,int dir){
  if(mem[dir].count(p))return mem[dir][p];
  int Dy[]={-1,-1,1,1};
  int Dx[]={-1,1,1,-1};
  int dy=Dy[dir];
  int dx=Dx[dir];
  int y=p.first+dy;
  int x=p.second+dx;
  while(inField(y+dy,x)&&t[y+dy][x]=='o')y+=dy;
  while(inField(y,x+dx)&&t[y][x+dx]=='o')x+=dx;
  return mem[dir][p]=P(y+dy,x+dx);
}

void put(P p,int dir){
  int y=p.first;
  int x=p.second;
  int dy[]={-1,0,1,0};
  int dx[]={0,1,0,-1};
  T[y][x]=false;
  while(inField(y,x)&&!T[y][x]){
    T[y][x]=true;
    y+=dy[dir];
    x+=dx[dir];
  }
}


set< P > st;

P solve(int ay,int ax,int by,int bx){
  P sp=P(-1,-1);
  P tmp=P(ay,ax);
  while(1){
    if(mem[2].count(tmp))break;
    tmp=search(tmp,2);
    if(!inField(ay,ax,by,bx,tmp))break;
    if(st.count(tmp)){
      sp=tmp;
    }
    st.insert(tmp);
  }
  tmp=P(by,ax);
  while(1){
    if(mem[1].count(tmp))break;
    tmp=search(tmp,1);
    if(!inField(ay,ax,by,bx,tmp))break;
    if(st.count(tmp)){
      sp=tmp;
    }
    st.insert(tmp);
  }
  if(sp.first==-1)return P(-1,-1);
  if(sp.first<=ay || sp.second<=ax)return P(-1,-1);
  if(sp.first>=by || sp.second>=bx)return P(-1,-1);
  P LU=solve(ay,ax,sp.first,sp.second);
  P LD=solve(sp.first,ax,by,sp.second);
  P RU=solve(ay,sp.second,sp.first,bx);
  P RD=solve(sp.first,sp.second,by,bx);
  if(LU.first!=-1)G[ sp ].push_back(LU);
  if(LD.first!=-1)G[ sp ].push_back(LD);
  if(RU.first!=-1)G[ sp ].push_back(RU);
  if(RD.first!=-1)G[ sp ].push_back(RD);
  
  //  if(LU.first!=-1)G[ sp.first ][sp.second].push_back(LU);
  //  if(LD.first!=-1)G[ sp.first ][sp.second].push_back(LD);
  //  if(RU.first!=-1)G[ sp.first ][sp.second].push_back(RU);
  //  if(RD.first!=-1)G[ sp.first ][sp.second].push_back(RD);
  return sp;
}

int main(){
  

  scanf("%d",&N);
  bool flag=false;
  for(int i=0;i<N;i++){
    scanf("%s",t[i]);
    for(int j=0;j<N;j++)
      if(t[i][j]=='x')flag=true;
  }
  if(!flag){
    cout<<0<<endl;
    return 0;
  }
  
  P sp=solve(-1,-1,N,N);

  map<P,bool> flg;
  priority_queue< P , vector<P> , greater<P> > Q;
  flg[ sp ]=true;
  Q.push( sp );
  
  vector<P> ans;
  while(!Q.empty()){
    P p=Q.top();

    Q.pop();
    ans.push_back(p);

    if(T[p.first][p.second]){
      printf("-1\n");
      return 0;
    }
    
    for(int i=0;i<4;i++){
      put(p,i);
    }
        
    for(int i=0;i<(int)G[p].size();i++){
      P to=G[p][i];
      if(to==P(-1,-1))continue;
      if(flg[to])continue;
      if(!inField(to))continue;
      flg[to]=true;
      Q.push(to);
    }
  }

  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if( (t[i][j]=='x') != T[i][j] ){
        printf("-1\n");
        return 0;
      }
    }
  }

  printf("%d\n",(int)ans.size());
  for(int i=0;i<(int)ans.size();i++){
    printf("%d\n",ans[i].first+1);
    printf("%d\n",ans[i].second+1);
  }
  return 0;
}

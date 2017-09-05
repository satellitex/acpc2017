#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;

int N;
char t[2005][2005];
bool T[2005][2005];
int a[2005][2005];
int b[2005][2005];

bool inField(int y,int x){
  return (0<=y&&y<N&&0<=x&&x<N);
}

bool inField(P p){
  return inField(p.first,p.second);
}

P dfs(P p,int dy,int dx){
  int y=p.first+dy;
  int x=p.second+dx;
  while(inField(y+dy,x)&&t[y+dy][x]=='o')y+=dy;
  while(inField(y,x+dx)&&t[y][x+dx]=='o')x+=dx;
  return P(y+dy,x+dx);
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

int main(){
  scanf("%d",&N);
  for(int i=0;i<N;i++)scanf("%s",t[i]);
  P sp=P(-1,-1);
  set<P> st;
  
  P tmp=P(-1,-1);
  while(1){
    tmp=dfs(tmp,1,1);
    if(!inField(tmp.first,tmp.second))break;
    st.insert(tmp);
  }
  tmp=P(N,-1);
  while(1){
    tmp=dfs(tmp,-1,1);
    if(!inField(tmp.first,tmp.second))break;
    if(st.count(tmp)){
      sp=tmp;
      break;
    }
  }
  if(sp.first==-1){
    printf("-1\n");
    return 0;
  }
  
  map<P,bool> flg;
  priority_queue< P , vector<P> , greater<P> > Q;
  flg[ sp ]=true;
  Q.push( sp );
  int dy[]={-1,-1,1,1};
  int dx[]={-1,1,1,-1};

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
    for(int i=0;i<4;i++){
      P to=dfs(p,dy[i],dx[i]);
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


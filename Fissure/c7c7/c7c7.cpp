#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> P;

#define fi first
#define se second

#define MAX 2055

char s[MAX][MAX];

int n;

int dx1[]={0,0,1,-1};
int dy1[]={1,-1,0,0};
int dx2[]={1,-1};
int dy2[]={1,1};

int color[MAX][MAX];
int table[MAX][MAX];
int cnt[MAX][MAX];

bool used[2][MAX][MAX];
bool visited[MAX][MAX];

map<P,vector<P> >Tree;

vector<P>ans;

void BAD_END(){
	cout<<-1<<endl;
	exit(0);
}

void Input(){
	cin>>n;
	gets(s[0]);
	for(int i=0;i<n;i++){
		gets(s[i]);
	}
}

bool in(int a,int b){
	return !(a<0||a>=n||b<0||b>=n);
}

bool in2(int a,int b,pair<P,P> c){
	return !(c.fi.se>a||c.se.se<a||c.fi.fi>b||c.se.fi<b);
}

void area_paint(int x,int y,int k){
	color[y][x]=k;
	for(int i=0;i<4;i++){
		int x1=x+dx1[i];
		int y1=y+dy1[i];
		if(in(x1,y1)&&s[y1][x1]=='o'&&!color[y1][x1]){
			area_paint(x1,y1,k);
		}
	}
}

void pre_fill(){
	int k=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(s[i][j]=='o'&&!color[i][j]){
				area_paint(j,i,k++);
			}
		}
	}
}

P get_center(P p,int k,pair<P,P> v){
	P cent=P(-1,-1);
	int y=p.se,Y=p.se,p1;
	int x=p.fi,X=p.fi,p2;

	while(1){

	    while(used[k][y][x]){
	    	return P(-1,-1);
	    }

	    while(1){
		    if(in(y,x)&&s[y][x]=='o'){
			    y+=dy2[k];
		    }
		    else break;
	    }
	    y-=dy2[k];

	    while(1){
		    if(in(y,x)&&s[y][x]=='o'){
			    x+=dx2[k];
		    }
		    else break;
	    }
	    y+=dy2[k];

	    if(!in2(y,x,v)) break;

	    used[k][Y][X]=1;
	    cnt[y][x]++;
	    Y=y+dy2[k],X=x+dx2[k];

	    if(cnt[y][x]==2) cent=P(x,y);

	    y+=dy2[k];
	    x+=dx2[k];

	    //if(!in2(y,x,v)) break;
	}

	return cent;
}
P make_tree(int x1,int y1,int x2,int y2){

	if(color[y1][x1]==color[y2][x2])return P(-1,-1);

	P center;
	P tmp[4];
	pair<P,P>p;

	p=make_pair(P(x1,y1),P(x2,y2));

	tmp[0]=P(x1,y1);
	tmp[1]=P(x2,y1);
	tmp[2]=P(-1,-1);
	tmp[3]=P(-1,-1);

	for(int i=0;i<2;i++){
		center=get_center(tmp[i],i,p);
		if(center.fi!=-1){
			break;
		}
		tmp[i]=P(-1,-1);
	}

	if(center.fi!=-1)tmp[0]=make_tree(x1,y1,center.fi-1,center.se-1);
	if(center.fi!=-1)tmp[1]=make_tree(center.fi+1,y1,x2,center.se-1);
	if(center.fi!=-1)tmp[2]=make_tree(x1,center.se+1,center.fi-1,y2);
	if(center.fi!=-1)tmp[3]=make_tree(center.fi+1,center.se+1,x2,y2);

	for(int i=0;i<4;i++){
		Tree[center].push_back(tmp[i]);
	}

	return center;
}

void priority_sort(P center){

	priority_queue<P,vector<P>,greater<P> >q;
	q.push(P(center.se,center.fi));

	while(!q.empty()){

		center=q.top();q.pop();
		if(center.fi==-1)continue;

		ans.push_back(center);

		for(int i=0;i<Tree[P(center.se,center.fi)].size();i++){
			q.push(P(Tree[P(center.se,center.fi)][i].se,Tree[P(center.se,center.fi)][i].fi));
		}
	}
}

void cross_fill(P p){
	for(int i=0;i<4;i++){
		int y=p.fi;
		int x=p.se;
		while(1){
			y+=dy1[i];
			x+=dx1[i];
			if(in(y,x)&&s[y][x]=='x'){
				visited[y][x]=1;
				table[y][x]=1;
			}
			else if(visited[y][x]) break;
			else if(s[y][x]=='x'){
				BAD_END();
			}
			else break;
		}
	}
	table[p.fi][p.se]=1;
	visited[p.fi][p.se]=1;
}

void fill_table(){
	for(int i=0;i<ans.size();i++){
		cross_fill(ans[i]);
	}
}

void error_check(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(s[i][j]=='x'&&!table[i][j]){
				BAD_END();
			}
		}
	}
}

void Output(){

	cout<<ans.size()<<endl;

	for(int i=0;i<ans.size();i++){
		cout<<ans[i].fi+1<<endl<<ans[i].se+1<<endl;
	}
}

main(){
	P center;
	Input();
	pre_fill();
	center=make_tree(0,0,n-1,n-1);
	priority_sort(center);
	fill_table();
	error_check();
	Output();
}
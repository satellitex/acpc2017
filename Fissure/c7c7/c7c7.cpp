#include<bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
#define R(i,a,n) for(int i=a;i<n;i+=2)
using namespace std;
typedef pair<int,int>P;
#define fi first
#define se second
#define mk make_pair
int num=1,col[2055][2055],n,num2=1;
int koko[2055][2055],topo[2055];
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
P zahyo[2055];
string s[2055];
vector<int>v[300000],rv[300000],lv[300000];
set<pair<pair<int,int>,pair<int,int> > >st;
bool used[300000],vi[300000];
void ravel_number(){
	R(i,1,n-1)R(j,1,n-1){
	  if(s[i][j]=='x'&&!col[i][j]){
		int cnt=0;
		r(k,4){
			int x=j+dx[k];
			int y=i+dy[k];
			if(s[y][x]=='x'&&!col[y][x])cnt++;
		}
		if(cnt==4){
			r(k,4){
				int y=i,x=j;
				while(1){
					y+=dy[k];
					x+=dx[k];
					if(y<0||y>=n||x<0||x>=n||s[y][x]=='o'||col[y][x])break;
					int cnt2=0;
					r(l,2){
						int yy=y+dy[(k+l*2+1)%4];
					    int xx=x+dx[(k+l*2+1)%4];
					    if(yy<0||yy>=n||xx<0||xx>=n)continue;
					    if(s[yy][xx]=='x'&&!col[yy][xx])cnt2++;
					}
					if(cnt2>=2)break;
					else col[y][x]=num;
				}
			}
			zahyo[num-1]=P(i,j);
			col[i][j]=num++;
			koko[i][j]=1;
		}
	  }
	}
}
void make_graph(){
	R(i,1,n-1)R(j,1,n-1){
	  if(col[i][j]){
		int cnt=0;
		r(k,4){
			int x=j+dx[k];
			int y=i+dy[k];
			if(s[y][x]=='x'&&col[y][x]==col[i][j])cnt++;
		}
		if(cnt==4){
			r(k,4){
				int y=i,x=j;
				while(1){
					y+=dy[k];
					x+=dx[k];
					if(y<0||y>=n||x<0||x>=n||s[y][x]=='o')break;
					if(s[y][x]=='x'&&col[i][j]!=col[y][x]&&!st.count( mk( mk(y,x) ,mk(i,j) ) )){
						v[col[y][x]-1].push_back(col[i][j]-1);
						rv[col[i][j]-1].push_back(col[y][x]-1);
						st.insert(mk(mk(y,x),mk(i,j)));
						break;
					}
				}
			}
		}
	  }
	}
}
void toporogical_sort(int p){
	used[p]=1;
	r(i,v[p].size())
	  if(!used[v[p][i]])
	  	toporogical_sort(v[p][i]);
	topo[p]=num2++;
}
void list_van(){
	r(i,num-1){
		int p=1e9,index=-1;
	    r(j,(int)rv[i].size()){
	    	if(topo[rv[i][j]]<p){
	    		p=topo[rv[i][j]];
	    		index=j;
	    	}
	    }
	    if(index==-1)continue;
	    lv[rv[i][index]].push_back(i);
	}
}
void print(int p){
	printf("%d\n%d\n",zahyo[p].fi+1,zahyo[p].se+1);
	vector<pair<P,int> >vp;
	r(i,lv[p].size()){
		vp.push_back(mk(mk(zahyo[lv[p][i]].fi,zahyo[lv[p][i]].se),lv[p][i]));
	}
	sort(vp.begin(),vp.end());
	r(i,vp.size()){
		print(vp[i].se);
	}
}
main(){
	cin>>n;
	r(i,n)cin>>s[i];

	r(i,n)r(j,n)if(s[i][j]=='x'&&(i%2==0)&&(j%2==0)){
		cout<<-1<<endl;
		return 0;
	}

	ravel_number();

	r(i,n)r(j,n)if(s[i][j]=='x'&&!col[i][j]){
		cout<<-1<<endl;
		return 0;
	}

	make_graph();

	r(i,num)if(!used[i])toporogical_sort(i);

	list_van();

	cout<<num-1<<endl;

	memset(used,0,sizeof(used));

	r(i,num-1)if(topo[i]==num-1)print(i);
}
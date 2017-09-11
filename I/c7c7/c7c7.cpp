#include <bits/stdc++.h>
using namespace std;
#define int long long
#define r(i,n) for(int i=0;i<n;i++)
#define MAX 100001
int ord[MAX],low[MAX],cost[MAX],a[MAX],n,m,x,y,o;
vector<int>v[MAX],v_[MAX];
int lowlink_ant_Lib(int p, int par) {
	int res=a[p];
    low[p]=ord[p]=o++;
    r(i,v[p].size()){
        if(ord[v[p][i]]==-1) {
        	v_[p].push_back(v[p][i]);
            res+=lowlink_ant_Lib(v[p][i],p);
            low[p]=min(low[p],low[v[p][i]]);
        }
        else if(v[p][i]!=par)
        	low[p]=min(low[p],ord[v[p][i]]);
    }
    return cost[p]=res;
}
main(){
	memset(ord,-1,sizeof(ord));
	cin>>n>>m;
	r(i,n)cin>>a[i];
	r(i,m){
		cin>>x>>y;
		v[--x].push_back(--y);
		v[y].push_back(x);
	}
	lowlink_ant_Lib(0,-1);
	r(i,n){
		int sum=cost[0]-cost[i],ans=0;
		r(j,v_[i].size()){
			if(ord[i]>low[v_[i][j]])sum+=cost[v_[i][j]];
			else ans=max(ans,cost[v_[i][j]]);
		}
		cout<<max(ans,sum)<<endl;
	}
}//解法を聞いたためsolved(?)
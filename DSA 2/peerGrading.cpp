#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <utility>

using namespace std;

typedef long long ll;
typedef vector<long long> vll;
typedef vector<int> vi;
typedef vector <vll> vvl;

ll getParent(vll&parent, ll x){
    if(parent[x]==x) return x;
    else{
        return parent[x]=getParent(parent, parent[x]);
    }
}
int m=0;

void union_rank(vll&parent, vll&rank, ll x, ll y){
    x=getParent(parent,x);
    y=getParent(parent,y);
    if(x==y) return;
    else{
        m++;
        if(rank[x]==rank[y]){
            rank[x]++;
            parent[y]=x;
        }
        if(rank[x]>rank[y]){
            parent[y]=x;
        }
        if(rank[x]<rank[y]){
            parent[x]=y;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
	freopen("in_exp.txt", "r", stdin);
	freopen("out_exp.txt", "w", stdout);
	#endif
    int t; cin>>t;
    while(t--){
        int n, flag=0; cin>>n;
        vvl inp(n, vll(n));
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin>>inp[i][j];
            }
        }
        if(n==1){
            if(inp[0][0]>0) cout<<inp[0][0]<<endl;
            else flag=1;
        }
        if(n!=1){
            vll edge_wt(n,-1);
            ll ans=0;
            vector<bool> visited(n,false);
            int selected_vertex=0;
            for(int i=0; i<n; i++){
                edge_wt[i]=inp[0][i];
            }
            //we have already visited the first vertex that is 0
            visited[0]=true;
            int edge_added=0;
            while(true){
                selected_vertex=-1;
                ll curr_min=1e10;
                for(int i=0; i<n; i++){
                    if(visited[i]==false && edge_wt[i]>0 && curr_min>edge_wt[i]){
                        selected_vertex=i;
                        curr_min=edge_wt[i];
                    }
                }
                if(curr_min==1e10) break;
                visited[selected_vertex]=true;
                ans+=curr_min;
                for(int i=0; i<n; i++){
                    if(visited[i]==false && inp[selected_vertex][i]>0){
                        edge_wt[i]>0 ? edge_wt[i]=min(inp[selected_vertex][i], edge_wt[i]) : edge_wt[i]=inp[selected_vertex][i];
                    }
                }
                edge_added++;
            }
            if(edge_added<n-1) cout<<"-1"<<endl;
            else cout<< (ll)2*ans<<endl;
        }
        if(flag) cout<<"-1"<<endl;
        /*if(n==1) {
            vvl inp(n, vll(n));
            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    cin>>inp[i][j];
                }
            }
            if(inp[0][0]==0)cout<<-1<<endl;
            else cout<< inp[0][0]<<endl;
        }
        else{
        vvl inp(n, vll(n));
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin>>inp[i][j];
            }
        }
        vvl graph; //cost, u, v
        vll parent(n+1), rank(n+1,0);
        for(int i=0; i<n ;i++){
            parent[i]=i; 
            for(int j=i; j<n; j++){
                if(inp[i][j])graph.push_back({inp[i][j], i, j});
            }
        }
        sort(graph.begin(), graph.end());
        ll ans=0;
        for(auto i: graph){
            int par_u=getParent(parent, i[1]);
            int par_v=getParent(parent, i[2]);
            if(par_u!=par_v){
                union_rank(parent, rank, i[1], i[2]);
                ans+=i[0];
            }
        }
        if(m==n-1) cout<<2*ans<<endl;
        else cout<<"-1"<<endl;
        }
        */
    }
    return 0;
}
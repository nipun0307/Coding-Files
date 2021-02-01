//MST (Kruskal) using DSU

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int getParent(vector <int>&p, int x){
    if(p[x]==x) return x;
    return p[x]=getParent(p, p[x]);
}

void union_set (vector<int>&parent, vector<int>&rank, long long u, long long v){
    u=getParent(parent, u);
    v=getParent(parent, v);
    if(u!=v){
        if(rank[u]==rank[v]){
            parent[v]=u;
            rank[u]++;
        }
        if(rank [u]>rank[v]){
            parent[v]=u;
        }
        if(rank[u]<rank[v]){
            parent[u]=v;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen("in_exp.txt","r", stdin);
        freopen("out_exp.txt", "w", stdout);

        int t;
        cin>>t;
        while(t--){
            int n; cin>>n;
            vector <int> parent(n+1);
            vector <int> rank(n+1,0);
            vector<vector<long long>> edges;    //every edge is a vector: (w, u, v) where w is a weight
            int k, cost;
            for(int j=1; j<=n; j++){
                string city;
                cin>>city;
                parent[j]=j;
                int degree; cin>>degree;
                for(int i=0; i<degree; i++){
                    cin>>k>>cost;
                    edges.push_back({cost,j,k});
                }
            }
            sort(edges.begin(), edges.end());
            int answer=0;
            for(auto e: edges){
                long long u=e[1], v=e[2], w=e[0];
                if(getParent(parent, u)!=getParent(parent, v)){
                    answer+=w;
                    union_set(parent, rank, u, v);
                }
            }
            //for(auto e: edges) cout<< e[1]<<" "<<e[2]<<"---"<<e[0]<<endl;
            cout<<answer<<endl;

        }
    #endif
}
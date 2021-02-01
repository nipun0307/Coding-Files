#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

#define tc 302
int node, edge, ar[tc];
//adjacency list
vector<int> adj [tc];
struct form_matroid{
    int identifier, start[tc], end[tc], isthere[tc], depth[tc];
    vector<pair<int,int>> graph[tc];
    // struct temp{
    //     int u, v;
    // }
    struct n_num{
        int a, b;
    }num[tc];
    void emp(){
        for (int i=1; i<=node; i++){
            graph[i].clear();
            start[i]=end[i]=isthere[i]=depth[i]=0;
        }
    }
    
    void DFS(int u){
        for (auto i: graph[u]){
            int v= i.first;
            if(isthere[v]==0){
                start[v]=u;
                end[v]=i.second;
                isthere[v]=isthere[u];
                depth[v]=depth[u]+1;
                DFS(v);
            }
        }
    }
    void dependent(int l){
        int u=num[l].a;
        int v=num[l].b;
        if(depth[u]<depth[v]) swap(u,v);
        while(depth[u]>depth[v]){
            if(identifier==0) adj[end[u]].push_back(l);
            else adj[l].push_back(end[u]);
            u=start[u];
        }
        while(u!=v){
            if(identifier==0) adj[end[u]].push_back(l);
            else adj[l].push_back(end[u]);
            u=start[u];
            if(identifier==0) adj[end[v]].push_back(l);
            else adj[l].push_back(end[v]);
            v=start[v];
        }
    }
    void lets_start(){  //initialising
        for(int i=1; i<=edge ; i++){
            if(ar[i]==0) continue;
            graph[num[i].a].push_back(make_pair(num[i].b,i));
            graph[num[i].b].push_back(make_pair(num[i].a,i));
        }
        for(int i=1; i<=node; i++)
            depth[i]=isthere[i]=0;
        int he=0;
        for(int i=1; i<=node;i++)
            if(isthere[i]==0){
                isthere[i]=++he;
                DFS(i);
            }
    }


}mat[2];

int queue[tc], visited[tc], pairing[2][tc], early[tc];


bool queries_satisfy(){
    for(int i=0; i<2; i++) mat[i].lets_start();
    for(int i=1; i<=edge; i++){
        if(ar[i]) continue;
        int var=0;
        while(var<2){
            var++;
            int u=mat[var].num[i].a;
            int v=mat[var].num[i].b;
            if(mat[var].isthere[u]!=mat[var].isthere[v])
                pairing[var][i]=1;
            else mat[var].dependent(i);
        }
    }
    //declairing variables for the defined queue
    int head=1;
    int tail=0;
    for(int i=1; i<=node;i++){
        if(pairing[0][i]!=0){
            tail++;
            queue[tail]=i;
            visited[i]=1;
        }
    }
    int temp=0;
    while(head<=tail){
        int u=queue[head];
        head++;
        if(pairing[1][u]!=0){
            temp=u;
            break;
        }
        for(auto i: adj[u]){
            if(visited[i]==0){
                visited[i]=1;
                early[i]=u; //updating the previous element
                tail++;
                queue[tail]=i;

            }
        }
    }
    if(!temp) return false; 
    while(temp){
        ar[temp]=ar[temp]^1; //if it is different from 1
        //if ar[temp]=1, ar[t] is updated to 0
        temp=early[temp];
    }
    return false;
}

void all_emp(){
    mat[0].emp();
            mat[1].emp();
            for(int i=1; i<=edge;i++){
                early[i]=visited[i]=0;
                pairing[0][i]=pairing[1][i]=0;
            }
}

int main(){
    freopen("in_exp.txt", "r", stdin);
	freopen("out_exp.txt", "w", stdout);
    int t, part_ans;
    cin>>t;
    mat[0].identifier=0;
    mat[1].identifier=1;
    while(t--){
        part_ans=0;
        cin>>node>>edge;
        for(int j=0; j<2; j++){
            for(int i=1; i<=edge; i++)
                cin>>mat[j].num[i].a>>mat[j].num[i].b;
        }
        for(int i=1; i<=edge; i++) ar[i]=0;
        
        while(queries_satisfy()){
            part_ans++;
            all_emp();
        }
        all_emp();
        int ans=2*node-part_ans-2;
        cout<<ans<<endl;
        
    }
    return 0;
}
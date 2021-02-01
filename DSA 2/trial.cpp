#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <utility>
using namespace std;

typedef long long ll;
typedef vector<long long> vll;

int getParent(int *parent,int a){
	if (parent[a] == a)
		return a;
	else{
	    parent[a] = getParent(parent,parent[a]);
	    return parent[a];
	}
}

void union_set(int *parent, int *size_f, int a, int b){
    int par_a, par_b;
	par_a = getParent(parent,a), par_b = getParent(parent,b);
	if (par_a==par_b) return;
	else{
		if (size_f[par_b] > size_f[par_a]){
    		parent[par_a] = par_b;
    		size_f[par_b] += size_f[par_a];
		}
		else {
    		parent[par_b] = par_a;
    		size_f[par_a] += size_f[par_b];
		}
	}
}

ll find_distance (int x, int y, vector<vll>&point, int d){
	ll temp=0;
	for(int i=0; i<d; i++){
		temp+=(point[x][i]-point[y][i])*(point[x][i]-point[y][i]);
	}
	return temp;
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
		int n, d;
		cin>>n>>d;
		vector<vll>point(n, vll(d));  ll ans=1;	//point stores the input
		for(int i=0; i<n ;i++){
			for(int j=0; j<d; j++) cin>>point[i][j];
		}

		vll edge_wt(n+1,0);	//since edge weight is the distance of the vertices, it will be atleast 0
		vector<bool> visited(n+1, false);
		int selected_vertex;
		ll div=747474747;
		//a variable sel_edge takes account binto the current edge
		//stand on a point, see through all the edges when visited[node]==false;
		//edge weight is updated to the maximum and edge wt is updated.
		// ans is updated and the visited is maximum 
		/*
		for(int i=0; i<n; i++){
			visited[selected_vertex]=true;
			ll max1=0; int temp=0;
			for(int j=0; j<n; j++){	//iterating through the selected vertex
				if(visited[j]==false && max1<distance[selected_vertex][j]){
					temp=j;
					max1=distance[selected_vertex][j];
				}
			}
			if(max1>0){
				ll max_2=0, ans_2;
				for(int i=0; i<n ;i++){
					if(visited[i]==true && max_2<distance[i][temp]) max_2=distance[i][temp];
				}
				edge_wt[selected_vertex]=ans_2=max(max1, max_2);
				selected_vertex=temp;
				ans=(ans*(ans_2%747474747))%747474747;
			}
			else
			{
				break;
			}
			
		}*/
		for(int i=1; i<n; i++){
			edge_wt[i]=find_distance(0,i, point, d);
		}
		visited[0]=true; //starting with this vertex
		while(true){	//the condition is always true. we need not check anything. It will exit the loop when it is done or when all distances are 0
			selected_vertex=-1;
			ll curr_max=0;
			for(int i=0; i<n; i++){	//iterating through the partners
				if(visited[i]==false && curr_max<edge_wt[i]){ //find max weight and index
					selected_vertex=i;
					curr_max=edge_wt[i];
				}
			}
			if(!curr_max) break; //iterated through all edges but still no luck
			visited[selected_vertex]=true;
			ans=(ans*(curr_max%div))%div;
			for(int i=0; i<n; i++){
				if(visited[i]==false){
					edge_wt[i]=max(edge_wt[i], find_distance(i,selected_vertex, point, d));
				}
			}
		}
		
		cout<<ans<<endl;

	}
	return 0;
}
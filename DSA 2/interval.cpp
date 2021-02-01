#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

#define N 20
vector<int> adj[N];
int nodes, edges, arr[N];


struct make_matroid
{
	int identifier;
	vector<pair<int, int> > graph[N];
	int start[N], end[N], isthere[N], depth[N];
	struct nums{
		int tem1, tem2;
	}num[N];
	
	void DFS(int u)
	{
		for (auto i: graph[u])
		{
			int v = i.first;
			if(!isthere[v]) 
			{
				start[v] = u;
				end[v] = i.second;
				depth[v] = depth[u]+1;
				isthere[v] = isthere[u];
				DFS(v);
			}
		}
	}
	void initialise()
	{
		for (int i = 1; i <= edges; ++i)
		{
			if (!arr[i]) continue;
			graph[num[i].tem1].push_back(make_pair(num[i].tem2, i));
			graph[num[i].tem2].push_back(make_pair(num[i].tem1, i));
	 	}
	 	for (int i = 1; i <= nodes; ++i)
	 		isthere[i] = 0, depth[i] = 0;
	 	for (int i = 1, t = 0; i <= nodes; ++i)
	 		if (!isthere[i]) isthere[i] = ++t, DFS(i);
	}
	
	void check_dependency(int i)
	{
		int u = num[i].tem1;
		int v = num[i].tem2;
		if (depth[u] < depth[v]) swap(u, v);
		while (depth[u] > depth[v])
		{
			if (identifier==0) adj[end[u]].push_back(i);
			else adj[i].push_back(end[u]);
			u = start[u];
		}
		while (u != v)
		{
			if (identifier==0) adj[end[u]].push_back(i);
			else adj[i].push_back(end[u]);
			u = start[u];
			if (identifier==0) adj[end[v]].push_back(i);
			else adj[i].push_back(end[v]);
			v = start[v];
		}
	}
	void clear()
	{
		for (int i = 1; i <= nodes; i++)
		{
		 	graph[i].clear();
		 	isthere[i] = start[i] = end[i] = depth[i] = 0;
	    }
	}
}Matroid[2];


int queue[N], visited[N], previous[N], pairings[2][N];

void check_again(int temp){
	while(temp){
		if(arr[temp]==1) arr[temp]=0;
		else arr[temp]=1;
		temp=previous[temp];
	}
}

bool lets_start()
{
	Matroid[0].initialise();
	Matroid[1].initialise();
	for (int i = 1; i <= edges; ++i)
	{
		if (arr[i]) continue;
		for (int k = 0; k <= 1; ++k)
		{
			if (Matroid[k].isthere[Matroid[k].num[i].tem1] != Matroid[k].isthere[Matroid[k].num[i].tem2])
			   pairings[k][i] = 1;
            else
            	Matroid[k].check_dependency(i);
		}
	}
	
	int head = 1, tail = 0, temp=0;
	for (int i = 1; i <= edges; ++i)
		if (pairings[0][i]) {queue[++tail] = i;
			visited[i] = 1;
	
		}

	while (head <= tail)
	{
		int u = queue[head];
		head++;
		if (pairings[1][u]) 
		{
			temp = u;
			break;
		}
		for (auto v: adj[u])
		{
			if (!visited[v])
			{
				visited[v] = 1;
				previous[v] = u;
				tail++;
				queue[tail] = v;
			}
		}
	}
	if (temp == 0) return false;
	
	check_again(temp);
	return true;
}


int main()
{
	freopen("in_exp.txt", "r", stdin);
	freopen("out_exp.txt", "w", stdout);
    int t, part_ans;
	cin>>t;
	Matroid[0].identifier = 0;
	Matroid[1].identifier = 1;
	while (t--)
	{
		part_ans=0;
		cin>>nodes>>edges;

		for (int k = 0; k <= 1; ++k)
			for (int i = 1; i <= edges; ++i)
				cin>>Matroid[k].num[i].tem1>>Matroid[k].num[i].tem2;

        for (int i = 1; i <= edges; ++i)
        	arr[i] = 0;
		while (lets_start()) 
		{
            part_ans++;
	 	  	Matroid[0].clear();
			Matroid[1].clear();
			for (int i = 1; i <= edges; ++i)
		{
			adj[i].clear();
			previous[i] = visited[i] = pairings[0][i] = pairings[1][i] = 0;
		}
        }
        Matroid[0].clear();
		Matroid[1].clear();
		for (int i = 1; i <= edges; ++i)
		{
			adj[i].clear();
			previous[i] = visited[i] = pairings[0][i] = pairings[1][i] = 0;
		}
		int ans=2*nodes-part_ans-2;
		cout<<ans<<endl;
	}
	return 0;
}

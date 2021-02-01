#include <iostream> 
#include <algorithm> 
#include <vector> 
using namespace std;

// lets say there are n rows and m columns (0 based indexing)
// now we the first row is 0 to m-1
// the second row (first index) should be m to 2m-1
// therefore, any cell is row[i]*m + col[i]

#define addr_of_cell(x,y) ((x) * (m ) + (y))    //giving a unique address to each cell

int maxSize;
int getParent(int *parent,int a){
	if (parent[a] == a)
		return a;
	else{
	    parent[a] = getParent(parent,parent[a]);
	    return parent[a];
	}
}

void union_set(int *parent, int*size_f, int a, int b){
    int par_a, par_b;
	par_a = getParent(parent,a), par_b = getParent(parent,b);
	if (par_a==par_b) return;
    // if(rank[par_a]>rank[par_b]){
    //     parent[par_b]=par_a;
    //     size[par_a]+=size[par_b];
    //     //size[par_b]=0;
    //     maxsize=max(maxsize, size[par_a]);
    // }
    // if(rank[par_a]==rank[par_b]){
    //     parent[par_b]=par_a;
    //     size[par_a]+=size[par_b];
    //     //size[par_b]=0;
    //     rank[par_a]++;
    //     maxsize=max(maxsize, size[par_a]);
    // }
    // if(rank[par_b]>rank[par_a]){
    //     parent[par_a]=par_b;
    //     size[par_b]+=size[par_a]; size[par_a]=0;
    //     maxsize=max(maxsize, size[par_b]);
    // }
	else{
		if (size_f[par_b] > size_f[par_a]){
    		parent[par_a] = par_b;
    		size_f[par_b] += size_f[par_a];
    		//size_f[par_b] = 0;
    		maxSize = max(maxSize, size_f[par_b]);
		}
		else {
    		parent[par_b] = par_a;
    		size_f[par_a] += size_f[par_b];
    		//size_f[par_b] = 0;
    		maxSize = max(maxSize, size_f[par_a]);
		}
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in_exp.txt","r",stdin);
		freopen("out_exp.txt","w",stdout);
	#endif
	int t;
	cin>>t;
	while (t--){
        int size_limit=1002; //highest possible array (+2 for safety)
        int right[size_limit][size_limit], down[size_limit][size_limit], parent[size_limit*size_limit], size_f[size_limit*size_limit];
        int n,m,q;
        cin>>n>>m>>q;
		vector<vector<int> > quer;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++){
				down[i][j] = right[i][j] = 0;
				parent[addr_of_cell(i, j)] = addr_of_cell(i, j);
				size_f[addr_of_cell(i, j)] = 1;
			}
		maxSize = 1;
		for(int i=0; i<q;i++){
		    int a;
			cin>>a;
			if (a == 1 || a == 2){
				int temp1, temp2;
                cin>>temp1>>temp2;
				quer.push_back({ a, --temp1, --temp2 });
				if (a == 1)
					right[temp1][temp2]++;
				else if (a==2)
					down[temp1][temp2]++;
			} else if (a == 3){
				int x1,y1,x2,y2;
                cin>>x1>>y1>>x2>>y2;
				quer.push_back({ a, --x1, --y1, --x2, --y2});
			}
			else if (a==4)
				quer.push_back({a});
		}
        reverse(quer.begin(), quer.end());
		for (int i = 0; i <n; i++)
			for (int j =0; j < m; j++){
				if (j < m-1 && !right[i][j])
					union_set(parent, size_f,addr_of_cell(i, j), addr_of_cell(i, j+1));
				if (i < n-1 && !down[i][j])
					union_set(parent,size_f,addr_of_cell(i, j), addr_of_cell(i+1, j));
			}
		long long ans = 0;
		for (auto i : quer){
			if (i[0] == 4){
			    ans += maxSize;
            } else if (i[0] == 3){
				if(getParent(parent,addr_of_cell(i[1], i[2])) == getParent(parent,addr_of_cell(i[3], i[4]))) ans += 1;
			} else if (i[0] == 1){
					if (right[i[1]][i[2]] ==1)
						union_set(parent,size_f,addr_of_cell(i[1], i[2]), addr_of_cell(i[1], i[2]+1));
					else right[i[1]][i[2]]--;
			} else if (i[0]==2){
					if (down[i[1]][i[2]] == 1)
						union_set(parent,size_f,addr_of_cell(i[1], i[2]), addr_of_cell(i[1]+1, i[2]));
					else down[i[1]][i[2]] --;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
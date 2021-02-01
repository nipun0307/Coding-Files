#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <iterator>
#include <utility>
using namespace std;


bool compare (const vector <int>&v1, const vector<int> &v2){
    if(v1[1]<v2[1]) return true;
    return false;
}

int main(){
    
    #ifndef ONLINE_JUDGE
        freopen("in_exp.txt","r",stdin);
        freopen("out_exp.txt","w",stdout);
    #endif
    int t;
    cin>>t;
    while(t--){
        vector <vector<int>>inp;
        int n, x;
        cin>>n>>x;
        int var1=0, var2=0;
        for(int i=0; i<n;i++){
            int a, b;
            cin>>a>>b;
            vector<int> tem;
            tem.push_back(a);
            tem.push_back(b);
            tem.push_back(-1);      //unvisited
            inp.push_back(tem);
        }
        sort(inp.begin(), inp.end(), compare);
        for(int i=0; i<n; i++){
            var1=var2=0;
            vector<int> tot_friends;
            for(int j=i; j<n; j++){
                if(inp[i][1]>=inp[j][0] && inp[j][2]==-1){
                    var1++;
                    tot_friends.push_back(j);
                }
            }
            while(var2+x<var1+1){
                inp[tot_friends[var1-var2-1]][2]=0;
                var2++;
            }
        }
        int ans=0;
        for(auto i: inp){
            ans+=i[2]+1;
        }
        cout<<ans<<endl;

        
    }
    return 0;
}
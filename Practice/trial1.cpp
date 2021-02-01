#include <iostream>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen("in_exp.txt","r", stdin);
        freopen("out_exp.txt", "w", stdout);
    #endif
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        string s;
        cin>>s;
        int to_remove=0;
        stack<char> temp;
        for(int i=0; i<s.length(); i++){
            if(temp.empty()) temp.push(s[i]);
            else{
                if(temp.top()=='1' && s[i]=='0') {   //decreasing
                    to_remove++; 
                    temp.pop(); //the stack should always be increase or const
                }
                else{
                    temp.push(s[i]);
                }
            }
        }
        cout<<to_remove<<"\n";
    }
    return 0;
}

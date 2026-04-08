#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 1;
int8_t cnt[MAXN];

void countIt(){
    for(int p = 2; p<MAXN; p++){
        if(cnt[p]==0){
            for(int prime=p; prime<MAXN; prime+=p){
                cnt[prime]++;
            }
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    countIt();
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        cout<<(1<<cnt[n])<<'\n';
    }
    return 0;
}
    
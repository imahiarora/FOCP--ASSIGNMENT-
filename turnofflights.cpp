#include<bitset>/stdc++.h>
using namespace std;

bool canDo(const strings& bulbs, int n, int l, int k){
    int operations =0;
    int i=0;
    while(i<n){
        if(bulbs[i]=='1'){
            operations++;
            if(operatios>k)return false;
            i+=l;
        }
        else{
            i++;
        }
    }
    return true;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k;
    cin>>n>>k;
    string bulbs;
    cin>>bulbs;

    int l1=1,high=n,ans=n;
    while(l1<=high){
        int midway =(l1+high)/2;
        if(canDo(bulbs,n,midway,k)){
            ans=midway;
            high=midway-1;
        }
        else{
            l1=midway+1;
        }
    }
    cout<<ans<<endl;
    return 0;

}





    
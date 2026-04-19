#include<bitset>/stdc++.h>
using namespace std;

int main(){
    long long l,r;
    cin >> l >> r;

    long long odd_count = (r+1)/2-(l/2);

    if(odd_count % 2 ==1)
    cout << "odd";
    else 
    cout << "even";
    
    return 0;
}



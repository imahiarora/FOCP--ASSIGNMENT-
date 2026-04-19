#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> choc(N);
        for (int j = 0; j < N; j++) {
            cin >> choc[j];
        }
        sort(choc.begin(), choc.end(), greater<int>());
        unordered_set<int> alex_used, bob_used;
        int a = 0, b = 0;
        int turn = 0;
        for (int i = 0; i < N; i++) {
            if (turn % 2 == 0) {
                if (alex_used.count(choc[i])) continue;
                alex_used.insert(choc[i]);
                a += choc[i];
            } else {
                if (bob_used.count(choc[i])) continue;
                bob_used.insert(choc[i]);
                b += choc[i];
            }
            turn++;
        }
        if (a > b) cout << "Alex" << endl;
        else cout << "Bob" << endl;
    }
    return 0;
}
#include<iostream>
#include<map>
#include<string>
using namespace std;

class Bank {
    unordered_map<string, long long> accounts;
    
public:
    bool create(string userId, long long amount) {
        if (accounts.find(userId) == accounts.end()) {
            accounts[userId] = amount;
            return true;
        }
        accounts[userId] += amount;
        return false;
    }
    
    bool debit(string userId, long long amount) {
        if (accounts.find(userId) == accounts.end() || accounts[userId] < amount)
            return false;
        accounts[userId] -= amount;
        return true;
    }
    
    bool credit(string userId, long long amount) {
        if (accounts.find(userId) == accounts.end())
            return false;
        accounts[userId] += amount;
        return true;
    }
    
    long long balance(string userId) {
        if (accounts.find(userId) == accounts.end())
            return -1;
        return accounts[userId];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int Q;
    cin >> Q;
    
    Bank bank;
    
    while (Q--) {
        string op;
        cin >> op;
        
        if (op == "CREATE") {
            string userId;
            long long amount;
            cin >> userId >> amount;
            cout << (bank.create(userId, amount) ? "true" : "false") << "\n";
        }
        else if (op == "DEBIT") {
            string userId;
            long long amount;
            cin >> userId >> amount;
            cout << (bank.debit(userId, amount) ? "true" : "false") << "\n";
        }
        else if (op == "CREDIT") {
            string userId;
            long long amount;
            cin >> userId >> amount;
            cout << (bank.credit(userId, amount) ? "true" : "false") << "\n";
        }
        else if (op == "BALANCE") {
            string userId;
            cin >> userId;
            cout << bank.balance(userId) << "\n";
        }
    }
    
    return 0;
}
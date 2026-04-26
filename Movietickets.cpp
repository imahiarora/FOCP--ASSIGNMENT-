#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

class MovieTicket {
    unordered_map<string, unordered_set<string>> bookings;
    static const int MAX_SLOTS = 100;

public:
    bool book(const string& customerId, const string& movieId) {
        auto& seats = bookings[movieId];
        if (seats.count(customerId) || (int)seats.size() >= MAX_SLOTS)
            return false;
        seats.insert(customerId);
        return true;
    }

    bool cancel(const string& customerId, const string& movieId) {
        auto it = bookings.find(movieId);
        if (it == bookings.end() || !it->second.count(customerId))
            return false;
        it->second.erase(customerId);
        return true;
    }

    bool isBooked(const string& customerId, const string& movieId) {
        auto it = bookings.find(movieId);
        if (it == bookings.end()) return false;
        return it->second.count(customerId) > 0;
    }

    int availableTickets(const string& movieId) {
        auto it = bookings.find(movieId);
        int booked = (it == bookings.end()) ? 0 : (int)it->second.size();
        return MAX_SLOTS - booked;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    cin >> Q;

    MovieTicket mt;

    while (Q--) {
        string op;
        cin >> op;

        if (op == "BOOK") {
            string customerId, movieId;
            cin >> customerId >> movieId;
            cout << (mt.book(customerId, movieId) ? "true" : "false") << "\n";
        }
        else if (op == "CANCEL") {
            string customerId, movieId;
            cin >> customerId >> movieId;
            cout << (mt.cancel(customerId, movieId) ? "true" : "false") << "\n";
        }
        else if (op == "IS_BOOKED") {
            string customerId, movieId;
            cin >> customerId >> movieId;
            cout << (mt.isBooked(customerId, movieId) ? "true" : "false") << "\n";
        }
        else if (op == "AVAILABLE_TICKETS") {
            string movieId;
            cin >> movieId;
            cout << mt.availableTickets(movieId) << "\n";
        }
    }

    return 0;
}
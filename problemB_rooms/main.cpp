// Problem B -- Minimum Meeting Rooms (Scheduling)
//
// Technique used: GREEDY (event sweep).
//
// Idea: Sort all start times and all end times separately. Walk through
// time using two pointers: whenever a meeting starts, we need one more
// room UNLESS a meeting has already ended by (<=) that time, in which
// case we can reuse a freed room. Track the running count of rooms in
// use and keep the maximum seen -- that maximum is the answer.
//
// Greedy-choice property: reusing the earliest-ending room whenever
// possible is always at least as good as opening a new one, because an
// available room can host any meeting that starts at or after that time.
//
// Input:
//   m
//   s1 e1
//   s2 e2
//   ...
//   sm em
// Output:
//   rooms

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;

    vector<long long> starts(m), ends(m);
    for (int i = 0; i < m; i++) {
        cin >> starts[i] >> ends[i];
    }

    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int rooms = 0, maxRooms = 0;
    int i = 0, j = 0;

    while (i < m) {
        if (starts[i] < ends[j]) {
            // A new meeting starts before the earliest currently-running
            // meeting ends -> need another room.
            rooms++;
            i++;
            maxRooms = max(maxRooms, rooms);
        } else {
            // A meeting ends at or before this start -> free a room.
            // (starts[i] >= ends[j] handles "same time = no overlap")
            rooms--;
            j++;
        }
    }

    cout << maxRooms << "\n";
    return 0;
}

// Problem C -- Budgeted Study Plan (0/1 Knapsack Variant)
//
// Technique used: DYNAMIC PROGRAMMING (0/1 knapsack).
//
// Idea: Let dp[b] = best value achievable using a time budget of exactly
// "up to b" hours, considering modules processed so far. For each module
// (time[i], value[i]) we update dp from the HIGH end of the budget down
// to time[i], so each module is only ever used once (0/1, not unbounded):
//     dp[b] = max(dp[b], dp[b - time[i]] + value[i])
// After processing all n modules, dp[T] holds the answer.
//
// Input:
//   n T
//   t1 v1
//   t2 v2
//   ...
//   tn vn
// Output:
//   best

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, T;
    if (!(cin >> n >> T)) return 0;

    vector<int> t(n);
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> v[i];
    }

    vector<ll> dp(T + 1, 0);

    for (int i = 0; i < n; i++) {
        // Iterate budget downward so each module is used at most once.
        for (int b = T; b >= t[i]; b--) {
            dp[b] = max(dp[b], dp[b - t[i]] + v[i]);
        }
    }

    ll best = dp[T];
    cout << best << "\n";
    return 0;
}

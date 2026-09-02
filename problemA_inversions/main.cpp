// Problem A  Inversion Counter for Quality Control
// Technique used: DIVIDE & CONQUER (merge sort).
// Idea: A brute-force $O(n^2)$ scan of every pair is too slow for $n$ up to $2 \times 10^5$. Instead, we count inversions while merge-sorting the array. When merging two already-sorted halves, every time we take an element from the right half before the left half is exhausted, that right element is smaller than all remaining elements in the left half, so it forms an inversion with each of them. We add that count in $O(1)$ per step, giving $O(n \log n)$ total.
// Input:
//   n
//   a1 a2 ... an
// Output:
//   inv   (number of inversions, fits in a 64-bit integer)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Merge two sorted halves a[l..m] and a[m+1..r], counting inversions.
ll mergeCount(vector<ll> &a, vector<ll> &tmp, int l, int m, int r) {
    ll inv = 0;
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            // a[i] > a[j]: a[j] is smaller than a[i..m], that's (m - i + 1) inversions
            inv += (m - i + 1);
            tmp[k++] = a[j++];
        }
    }
    while (i <= m) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];

    for (int x = l; x <= r; x++) a[x] = tmp[x];
    return inv;
}

ll sortCount(vector<ll> &a, vector<ll> &tmp, int l, int r) {
    if (l >= r) return 0;
    int m = l + (r - l) / 2;
    ll inv = 0;
    inv += sortCount(a, tmp, l, m);
    inv += sortCount(a, tmp, m + 1, r);
    inv += mergeCount(a, tmp, l, m, r);
    return inv;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> tmp(n);
    ll inv = (n > 1) ? sortCount(a, tmp, 0, n - 1) : 0;

    cout << inv << "\n";
    return 0;
}

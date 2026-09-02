# Report Algorithm Design Mini-Lab

This report covers all three problems: the idea behind each solution,
pseudocode, a worked example, and a complexity analysis.

---

## Problem A  Inversion Counter for Quality Control

### Problem summary

Given an array A of n integers, an inversion is a pair of indices
i < j such that A[i] > A[j] meaning, a "quality" defect where a later
element is smaller than an earlier one. The task is to count how many
such pairs exist. A naive check of every pair is `O(n^2)`, which is too
slow for n up to 2 * 10^5, so we need something closer to `O(n log n)`.

### Algorithm idea

This is a **divide & conquer** problem: it's essentially merge sort with
extra bookkeeping. Split the array into a left half and a right half,
recursively count inversions inside each half, then count inversions that
cross between the two halves while merging them back into sorted order.

The key trick is in the merge step. If both halves are already sorted,
then when we walk through them left-to-right and pick the next-smallest
element: every time the element we pick comes from the **right** half
before the left half is exhausted, that element is smaller than *all* the
remaining elements in the left half — each of those forms an inversion
with it. We can count all of them in one step (no need to check them one
by one), which is what keeps the merge step `O(n)` instead of `O(n^2)`.

Total inversions = (inversions fully inside left half) + (inversions
fully inside right half) + (inversions crossing the two halves, found
during merge).

### Pseudocode

```
function countInversions(A, n):
    tmp = array of size n
    return sortAndCount(A, tmp, 0, n - 1)

function sortAndCount(A, tmp, left, right):
    if left >= right:
        return 0                          # 0 or 1 elements: no inversions

    mid = left + (right - left) / 2
    inv = 0
    inv += sortAndCount(A, tmp, left, mid)
    inv += sortAndCount(A, tmp, mid + 1, right)
    inv += mergeAndCount(A, tmp, left, mid, right)
    return inv

function mergeAndCount(A, tmp, left, mid, right):
    i = left, j = mid + 1, k = left
    inv = 0
    while i <= mid and j <= right:
        if A[i] <= A[j]:
            tmp[k] = A[i]; i += 1
        else:
            # A[j] is smaller than A[i..mid]: that's (mid - i + 1) inversions
            inv += (mid - i + 1)
            tmp[k] = A[j]; j += 1
        k += 1
    copy any remaining A[i..mid]   into tmp, advancing k
    copy any remaining A[j..right] into tmp, advancing k
    copy tmp[left..right] back into A[left..right]
    return inv
```

### Example run

Input: `A = [2, 4, 1, 3, 5]`

- Split into `[2, 4]` and `[1, 3, 5]`.
- `[2, 4]` is already sorted internally → 0 inversions, merge is trivial.
- `[1, 3, 5]` splits into `[1]` and `[3, 5]` → 0 inversions each, merges
  cleanly → 0 inversions total on the right side.
- Merge `[2, 4]` with `[1, 3, 5]`:
  - Compare 2 vs 1 → 1 is smaller, comes from the right half while both
    elements of the left half (`2, 4`) remain → **+2 inversions**
    (pairs `(2,1)` and `(4,1)`).
  - Compare 2 vs 3 → 2 is smaller, take it from the left, no inversion.
  - Compare 4 vs 3 → 3 is smaller, comes from the right while `4` still
    remains on the left → **+1 inversion** (pair `(4,3)`).
  - Remaining element `5` copied over, no more comparisons needed.
- Total: `2 + 1 = 3`.

Output: `3` — matches the expected result.

### Complexity analysis

- **Time (worst case):** The recursion follows the standard merge-sort
  recurrence `T(n) = 2T(n/2) + O(n)` (the `O(n)` is the merge step, which
  does a constant amount of work per element). By the Master Theorem this
  solves to **`O(n log n)`**. This is worst-case, not just average-case,
  since merge sort's cost doesn't depend on the input's order.
- **Space:** `O(n)` for the temporary merge buffer, plus `O(log n)` for
  the recursion stack (the recursion depth is `log2(n)` since each call
  halves the range). Overall auxiliary space is **`O(n)`**.
- **Why 64-bit:** with `n = 2*10^5`, the maximum possible inversion count
  is `n*(n-1)/2 ≈ 2*10^10`, which overflows a 32-bit signed integer, so
  the running/returned count uses `long long` (`ll`).

---

## Problem B  Minimum Meeting Rooms (Scheduling)

### Problem summary

Given `m` meetings, each with a start and end time, find the minimum
number of rooms needed so that no room ever hosts two overlapping
meetings at once. Two meetings that touch at a single point (one ends
exactly when the other starts) are **not** considered overlapping.

### Algorithm idea

This is a **greedy** problem. Instead of thinking about which specific
meeting goes in which room, we only need to know the maximum number of
meetings that are simultaneously "in progress" at any instant — that
number is exactly the minimum number of rooms required.

To find that peak, treat every start time as a `+1` event (need a room)
and every end time as a `-1` event (a room frees up). Sort the starts and
the ends separately, then walk through the starts in order; for each
start, first free up any room whose meeting has already ended by (`<=`)
that start time. If no room is free, open a new one. Track the maximum
number of rooms in use at any time — that's the answer.

**Greedy-choice property:** freeing the earliest-ending room whenever
possible is always safe, because a room that's already free can host any
meeting starting at or after that point — there's never a reason to open
a new room while an existing one is already free.

### Pseudocode

```
function minRooms(meetings):                # meetings = list of (start, end)
    starts = sorted list of all start times
    ends   = sorted list of all end times

    rooms = 0
    maxRooms = 0
    i = 0   # pointer into starts
    j = 0   # pointer into ends

    while i < m:
        if starts[i] < ends[j]:
            # a meeting starts before the earliest running one ends
            rooms += 1
            i += 1
            maxRooms = max(maxRooms, rooms)
        else:
            # starts[i] >= ends[j]: that room is free (same-time touch is OK)
            rooms -= 1
            j += 1

    return maxRooms
```

### Example run

Input meetings: `(0, 30), (5, 10), (15, 20)`

- `starts = [0, 5, 15]`, `ends = [10, 20, 30]`
- `i=0, j=0`: `starts[0]=0 < ends[0]=10` → open a room. `rooms=1`,
  `maxRooms=1`. `i=1`.
- `starts[1]=5 < ends[0]=10` → open another room. `rooms=2`,
  `maxRooms=2`. `i=2`.
- `starts[2]=15`, compare to `ends[0]=10`: `15 >= 10` → free that room.
  `rooms=1`. `j=1`.
- Now `starts[2]=15 < ends[1]=20` → open a room again. `rooms=2`,
  `maxRooms` stays `2`. `i=3`, loop ends (`i == m`).

Output: `2` — matches the expected result (meeting `(0,30)` and meeting
`(5,10)` overlap and need separate rooms; `(15,20)` reuses whichever room
freed up first).

### Complexity analysis

- **Time (worst case):** Sorting the starts and ends dominates:
  `O(m log m)`. The subsequent sweep visits each start and each end
  exactly once, so it's `O(m)`. Total: **`O(m log m)`**.
- **Space:** The two sorted arrays of size `m` are the only extra
  storage (aside from sort's own working space), so auxiliary space is
  **`O(m)`**.
- **Correctness / greedy justification:** At any instant, the number of
  rooms needed is exactly the number of meetings currently in progress
  (an exchange argument shows you can never do better than the peak
  overlap, and the sweep achieves exactly that peak by always reusing a
  freed room before opening a new one).

---

## Problem C  Budgeted Study Plan (0/1 Knapsack Variant)

### Problem summary

There are `n` study modules, each costing `time[i]` hours and worth
`value[i]` points, and a total time budget `T`. Each module can be taken
at most once (0/1 — no partial credit, no repeats). The goal is to choose
a subset of modules that maximizes total value without the total time
exceeding `T`. This is the classic 0/1 knapsack problem.

### Algorithm idea

This is a **dynamic programming** problem, since brute-force subset
enumeration is `2^n`, infeasible for `n` up to 2000. Define
`dp[b]` = the best total value achievable using a time budget of at most
`b` hours, considering the modules processed so far.

Process modules one at a time. For each module `i`, we either skip it
(value stays `dp[b]`) or take it (value becomes `dp[b - time[i]] +
value[i]`, only possible if `b >= time[i]`); `dp[b]` is updated to the
better of the two. To guarantee each module is used **at most once**
(0/1, not unbounded), the inner loop over budgets must go from `T` down
to `time[i]` — updating in decreasing order ensures `dp[b - time[i]]`
still refers to a state from *before* module `i` was considered, so
module `i` can't be "reused" within the same pass.

After all `n` modules are processed, `dp[T]` is the answer.

### Pseudocode

```
function knapsack(n, T, time[1..n], value[1..n]):
    dp = array of size (T + 1), all initialized to 0

    for i = 1 to n:
        for b = T downto time[i]:          # downward: enforces 0/1 (no reuse)
            dp[b] = max(dp[b], dp[b - time[i]] + value[i])

    return dp[T]
```

### Example run

Input: modules `(time=3, value=4)`, `(time=4, value=5)`, `(time=7,
value=10)`, budget `T = 10`.

Start: `dp = [0,0,0,0,0,0,0,0,0,0,0]` (indices 0..10)

**Module 1 (t=3, v=4):** for `b` from 10 down to 3:
`dp[b] = max(dp[b], dp[b-3] + 4)`. Every `dp[b]` for `b >= 3` becomes `4`
(since it's the first module considered).
`dp = [0,0,0,4,4,4,4,4,4,4,4]`

**Module 2 (t=4, v=5):** for `b` from 10 down to 4:
e.g. `dp[7] = max(dp[7]=4, dp[3]+5=4+5=9) = 9`;
`dp[10] = max(dp[10]=4, dp[6]+5=4+5=9) = 9`.
`dp = [0,0,0,4,5,5,5,9,9,9,9]`

**Module 3 (t=7, v=10):** for `b` from 10 down to 7:
`dp[10] = max(dp[10]=9, dp[3]+10=4+10=14) = 14`;
`dp[7] = max(dp[7]=9, dp[0]+10=0+10=10) = 10`.
`dp = [0,0,0,4,5,5,5,10,9,9,14]`

Final: `dp[10] = 14`, achieved by taking module 1 (t=3,v=4) and module 3
(t=7,v=10): total time `3+7=10 <= 10`, total value `4+10=14`.

Output: `14` — matches the expected result.

### Complexity analysis

- **Time (worst case):** Two nested loops — outer over `n` modules, inner
  over budgets `1..T` — giving **`O(n * T)`**. With `n = 2000` and
  `T = 5000`, that's about `10^7` operations, comfortably fast. This is a
  tight bound (not just average case): every `(module, budget)` cell is
  visited exactly once regardless of input values.
- **Space:** Using a 1D rolling array of size `T + 1` (updated in
  decreasing order per module) rather than a full 2D `n x T` table gives
  **`O(T)`** space instead of `O(n * T)`. This is valid specifically
  *because* of the downward iteration, which recreates the effect of
  "looking only at the previous row" of the classic 2D DP table.
  Justification via DP table size: the standard formulation is a table
  `dp[i][b]` of size `(n+1) x (T+1)`, where each cell depends only on the
  row above it (`dp[i-1][...]`); collapsing it to one row is a standard
  space optimization since we never need rows older than "the previous
  one."
- **Correctness sketch:** By induction on `i`, after processing the first
  `i` modules, `dp[b]` holds the optimal value using any subset of those
  `i` modules with total time `<= b`. The recurrence
  `dp[i][b] = max(dp[i-1][b], dp[i-1][b - time[i]] + value[i])` directly
  encodes "skip module i" vs. "take module i," which are the only two
  choices for a 0/1 item — so the DP explores exactly the necessary
  subset space without brute-force enumeration.

---

## Summary table

| Problem | Technique | Time | Space |
|---|---|---|---|
| A — Inversions | Divide & conquer (merge sort) | O(n log n) | O(n) |
| B — Meeting rooms | Greedy (event sweep) | O(m log m) | O(m) |
| C — Knapsack | Dynamic programming | O(n·T) | O(T) |

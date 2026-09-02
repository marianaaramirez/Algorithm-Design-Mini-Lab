# Problem C — Budgeted Study Plan (0/1 Knapsack)

Given `n` study modules, each with a time cost and a value, picks a subset
(each module used at most once) that maximizes total value without
exceeding a time budget `T`.

Approach: **dynamic programming** — classic 0/1 knapsack with a 1D rolling
array `dp[budget]`, updated right-to-left per module so nothing is reused.
Runs in O(n·T) time, O(T) space.

## Build

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Run

```bash
./main
```

Input format:

```
n T
t1 v1
t2 v2
...
tn vn
```

Example:

```bash
echo "3 10
3 4
4 5
7 10" | ./main
```

Output:

```
14
```

## Tests

Run all tests with:

```bash
chmod +x tests/run_tests.sh
./tests/run_tests.sh
```

## Edge cases covered by tests

- General mixed case (`test1`)
- Every module's time exceeds `T` → answer 0 (`test2`)
- Multiple valid combinations, must pick the best (`test3`)
- Tight budget, exact fit vs. leftover budget (`test4`)

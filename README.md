# Algorithm-Design-Mini-Lab
Activity 1.1

Three small C++ programs, each solved with a different algorithm design
technique:

| Folder                | Problem                          | Technique        |
|------------------------|-----------------------------------|-------------------|
| problemA_inversions/ | Count inversions in an array      | Divide & conquer  |
| problemB_rooms/      | Minimum meeting rooms needed      | Greedy            |
| problemC_knapsack/    | Budgeted study plan (0/1 knapsack)| Dynamic programming |

Full write-up (idea, pseudocode, worked example, complexity analysis) for
each problem is in [`report.md`](./report.md).

## How to build and run each problem

All three programs read from **stdin** and write to **stdout** (no
interactive prompts), so you can pipe a file in or type input followed by
EOF (Ctrl+D).

### Problem A — Inversion Counter

```bash
cd problemA_inversions
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
echo "5
2 4 1 3 5" | ./main
# -> 3
```

### Problem B — Minimum Meeting Rooms

```bash
cd problemB_rooms
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
echo "3
0 30
5 10
15 20" | ./main
# -> 2
```

### Problem C — Budgeted Study Plan (0/1 Knapsack)

```bash
cd problemC_knapsack
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
echo "3 10
3 4
4 5
7 10" | ./main
# -> 14
```

## Running the tests

Each `problemX/` folder has a `tests/` directory with at least three
input/output pairs (`testN.in` / `testN.out`) and a `run_tests.sh` script
that compiles the program and diffs its output against every pair.

```bash
cd problemA_inversions && chmod +x tests/run_tests.sh && ./tests/run_tests.sh
cd ../problemB_rooms   && chmod +x tests/run_tests.sh && ./tests/run_tests.sh
cd ../problemC_knapsack && chmod +x tests/run_tests.sh && ./tests/run_tests.sh
```

Expected output for each: `Passed: N, Failed: 0`.

## Assumptions

- Input is well-formed and matches the stated I/O format exactly (no
  malformed-input handling is required per the assignment).
- All counts/sums that could exceed 32 bits (inversion count, knapsack
  value) are stored as `long long`.
- Problem B: a meeting that ends exactly when another starts does **not**
  count as an overlap (they can share a room).
- Problem C: each module can be selected at most once (0/1 knapsack, not
  fractional/unbounded).

## Repository layout

```
/problemA_inversions
    main.cpp
    README.md
    tests/
/problemB_rooms
    main.cpp
    README.md
    tests/
/problemC_knapsack
    main.cpp
    README.md
    tests/
report.md
README.md
```

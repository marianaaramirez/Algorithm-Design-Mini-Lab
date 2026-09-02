# Problem A — Inversion Counter for Quality Control

Counts the number of inversions in an array (pairs `i < j` with `A[i] > A[j]`).

Approach: **divide & conquer** — merge sort, counting cross-inversions during
each merge step. Runs in O(n log n).

## Build

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Run

```bash
./main
```

Then type/pipe input in this format:

```
n
a1 a2 ... an
```

Example:

```bash
echo "5
2 4 1 3 5" | ./main
```

Output:

```
3
```

## Tests

Three (plus one extra) input/output pairs live in `tests/`. Run them all with:

```bash
chmod +x tests/run_tests.sh
./tests/run_tests.sh
```

This compiles `main.cpp` and checks the output of every `tests/testN.in`
against the matching `tests/testN.out`.

## Edge cases covered by tests

- General case (`test1`)
- Already sorted (`test2` → 0 inversions)
- Reverse sorted (`test3` → maximum inversions)
- Duplicate values (`test4` → equal elements never count as inversions)

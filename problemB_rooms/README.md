# Problem B — Minimum Meeting Rooms (Scheduling)

Computes the minimum number of rooms needed to host `m` meetings without
overlap.

Approach: **greedy** event sweep — sort start times and end times
separately, then scan: a start needs a new room unless an earlier meeting
has already ended (`starts[i] >= ends[j]` frees a room, since ending at
the same time as another starts is not an overlap). Runs in O(m log m).

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
m
s1 e1
s2 e2
...
sm em
```

Example:

```bash
echo "3
0 30
5 10
15 20" | ./main
```

Output:

```
2
```

## Tests

Run all tests with:

```bash
chmod +x tests/run_tests.sh
./tests/run_tests.sh
```

## Edge cases covered by tests

- General overlap case (`test1`)
- Back-to-back meetings, no overlap since end == next start (`test2`)
- All meetings overlapping (`test3`)
- Nested intervals, one long meeting containing two short ones (`test4`)

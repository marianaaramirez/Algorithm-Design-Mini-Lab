#!/usr/bin/env bash
# Compiles main.cpp and runs every test*.in / test*.out pair in this folder.
set -e
cd "$(dirname "$0")/.."

g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main

pass=0
fail=0
for infile in tests/*.in; do
    base=$(basename "$infile" .in)
    expected="tests/${base}.out"
    actual=$(./main < "$infile")
    want=$(cat "$expected")
    if [ "$actual" == "$want" ]; then
        echo "[PASS] $base"
        pass=$((pass+1))
    else
        echo "[FAIL] $base (expected '$want', got '$actual')"
        fail=$((fail+1))
    fi
done

echo "----"
echo "Passed: $pass, Failed: $fail"

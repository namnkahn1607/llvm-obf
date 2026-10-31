#!/usr/bin/env bash

set -euo pipefail

# Transpile to LLVM IR at `-O0`
clang-18 -S -emit-llvm -O0 test.c -o test_O0.ll

# 1. `optnone` now appears in list of `attributes #0 = { ... }`.
# 2. Inside the function body of `define dso_local i32 @add_mba(...) #0`: 
#    `xor`, `and`, `mul` and `add` remains the same.

# Now re-transpile using `-O2` with `optnone` disabled
clang-18 -S -emit-llvm -O1 -Xclang -disable-llvm-passes test.c -o test_raw.ll
opt-18 -S -passes="default<O2>" test_raw.ll -o test_O2.ll

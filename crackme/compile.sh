#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(git rev-parse --show-toplevel)"
cd "$REPO_ROOT"

clang-18 -O0 crackme/crackme1-2.c -o build/crackme12
clang-18 -O0 crackme/crackme3.c -o build/crackme3
clang-18 -O0 crackme/crackme4.c -o build/crackme4
clang-18 -O0 crackme/crackme5.c -o build/crackme5

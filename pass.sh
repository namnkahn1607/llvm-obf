#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(git rev-parse --show-toplevel)"

log()  { echo "[INFO] $*" >&2; }
warn() { echo "[WARN] $*" >&2; }
die()  { echo "[ERROR] $*" >&2; exit 1; }

cmake -B build

BUILD_DIR="$REPO_ROOT/build"
cd "$BUILD_DIR"
make

cd "$REPO_ROOT"
clang-18 -S -emit-llvm -O0 inputs/sanity.c -o build/sanity.ll

cd "$BUILD_DIR"
opt-18 -load-pass-plugin=./MbaPass.so -passes="mba" -S sanity.ll -o sanity_opt.ll

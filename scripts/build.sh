#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$PROJECT_ROOT"

cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Debug

cmake --build build

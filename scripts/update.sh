#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "$0")"/.. && pwd)"
cd "$PROJECT_ROOT"

if [ ! -d "build" ]; then
    echo "[INFO] Build directory not found. Configuring project..."
    cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Debug
fi

cmake --build build
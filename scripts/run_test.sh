#!/bin/bash

set -e

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$PROJECT_ROOT"


if [ ! -f "build/tests/teststring" ] || [ ! -f "build/tests/testnumber" ]; then
    echo "[INFO] Test binaries not found. Building project first..."
    exit 1;
fi

echo "[INFO] Running tests via CTest..."

DATA_FILE_NAME="tests/data/names.txt"
DATA_FILE_NUMBER="tests/data/numbers.txt"

MODE="$1"

case "$MODE" in
    1)
        echo "[INFO] Running TEST 1: String / Name Test..."
        ./build/tests/teststring "$DATA_FILE_NAME"
        ;;
    2)
        echo "[INFO] Running TEST 2: Number Test..."
        ./build/tests/testnumber "$DATA_FILE_NUMBER"
        ;;
    3)
        echo "[INFO] Running TEST 3: Type Safety & Compile-Time Checks..."
        ./build/tests/test_typesafety
        ;;
    *)
        echo "[INFO] Running ALL tests..."
        ./build/tests/teststring "$DATA_FILE_NAME"
        ./build/tests/testnumber "$DATA_FILE_NUMBER"
        ;;
esac
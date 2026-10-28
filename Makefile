.PHONY: default help build b run r all update u clean c r1 r2

default: help

help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  b, build   Build project (CMake + Ninja)"
	@echo "  r, run     Run unit tests"
	@echo "  all        Build and run tests immediately"
	@echo "  c, clean   Remove build directory (clean cache)"
	@echo "  u, update  Update build directory"

b: build
build: 
	@bash scripts/build.sh

u: update
update:
	@bash scripts/update.sh

r: run
run: 
	@bash scripts/run_test.sh

r1: 
	@bash scripts/run_test.sh 1

r2:
	@bash scripts/run_test.sh 2

r3:
	@bash scripts/run_test.sh 3

all: build run


c: clean
clean:
	@echo "[INFO] Cleaning build directory..."
	@rm -rf build/
	@echo "[INFO] Clean finished."
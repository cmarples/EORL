#!/bin/bash

# Run this from the root directory!
# 	./scripts/quick_rebuild_project.sh

BUILD_DIR="build"

cd "$BUILD_DIR"

echo "Running CMake..."
cmake ..
echo "Building the project..."
make
echo "Rebuild complete."

echo "Run unit tests..."
cd ..
./bin/unit_tests.exe
echo "script: quick_rebuild_project.sh is complete!"
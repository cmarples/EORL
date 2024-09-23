#!/bin/bash

# Run this from the root directory!
# 	./scripts/rebuild_project.sh

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning up the existing build directory..."
    rm -rf "$BUILD_DIR"
else
    echo "No existing build directory found, skipping cleanup."
fi

echo "Creating build directory..."
mkdir "$BUILD_DIR"
cd "$BUILD_DIR" || exit

echo "Running CMake..."
cmake ..
echo "Building the project..."
make
echo "Rebuild complete."

echo "Generating documentation..."
cd ../docs
doxygen Doxyfile
echo "Documentation generation complete!"

echo "Run unit tests..."
cd ..
./bin/unit_tests.exe
echo "script: rebuild_project.sh is complete!"
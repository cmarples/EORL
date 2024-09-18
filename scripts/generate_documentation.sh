#!/bin/bash

# Run this from the root directory!
# 	./scripts/generate_documentation.sh

echo "Generating documentation..."
cd ../docs
doxygen Doxyfile
echo "script: generate_documentation.sh is complete!"
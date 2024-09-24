#!/bin/bash

# Ensure the script is run as a superuser
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

# Check if the filename argument is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

fname="$1"

# Move up one directory
cd ..

# Build Nachos
echo "Building Nachos..."
if ! ./build_nachos.sh; then
    echo "Failed to build Nachos"
    exit 1
fi

cd code/test/
make clean
make

cd ../../

# Build tests
# echo "Building tests..."
# if ! ./build_test.sh; then
#     echo "Failed to build tests"
#     exit 1
# fi

# Change to the build directory
cd code/build.linux

# Run Nachos with the provided test file
echo "Running Nachos with test file: ${fname}..."
if ! ./nachos -x ../test/${fname}; then
    echo "Failed to run Nachos with ${fname}"
    exit 1
fi

echo "Script completed successfully."
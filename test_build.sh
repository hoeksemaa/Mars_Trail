#!/bin/bash
set -e

echo "Building Test Mars Trail..."

# check for gcc
if ! command -v gcc &> /dev/null; then
	echo "Error: gcc not found. Please install a C compiler."
	exit 1
fi

# compile
gcc -Wall -Wextra -std=c99 -o Test_Mars_Trail Test_Mars_Trail.c

# check if build succeeded
if [ $? -eq 0 ]; then
	echo "Build successful! Run with: ./Test_Mars_Trail"
else
	echo "Build failed!"
	exit 1
fi

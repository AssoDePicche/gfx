#!/bin/bash

BUILD_TYPE=${1:-Release}

set -e

echo "Building Gfx binary via Docker..."

rm -f Gfx Gfx-linux-x86_64

docker build --build-arg BUILD_TYPE=$BUILD_TYPE --build-arg BUILDKIT_INLINE_CACHE=1 --target exporter --output type=local,dest=. --progress=plain .

echo "Build complete: ./Gfx-linux-x86_64"

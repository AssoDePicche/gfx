#!/bin/bash

set -e

echo "Building Gfx binary via Docker..."

rm -f Gfx Gfx-linux-x86_64

docker build --target exporter --output type=local,dest=. .

echo "Build complete: ./Gfx-linux-x86_64"

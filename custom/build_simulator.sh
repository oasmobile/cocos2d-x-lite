#!/bin/sh

cd "$(dirname "$0")"
cd ..

gulp gen-simulator
gulp update-simulator-config

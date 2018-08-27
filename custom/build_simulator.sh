#!/bin/sh

cd "$(dirname "$0")"
cd ..

gulp sign-simulator
gulp gen-simulator
gulp update-simulator-config

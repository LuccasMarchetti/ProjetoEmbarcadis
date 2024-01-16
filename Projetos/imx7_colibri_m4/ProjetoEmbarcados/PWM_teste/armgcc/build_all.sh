#!/bin/sh
export ARMGCC_DIR=~/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/
cd debug/
./build_debug.sh
cd ..
cd release/
./build_release.sh
cd ..

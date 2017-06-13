#!/usr/bin/env bash

gcc SegFault.c -o ./bin/SegFault -ggdb
./bin/SegFault
echo "SegFault return code: $?"
#gdb ./bin/SegFault

gcc NormalRun.c -o ./bin/NormalRun 
./bin/NormalRun
echo "NormalRun return code : $?"

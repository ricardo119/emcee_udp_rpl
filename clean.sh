#!/bin/bash
# Execute: "chmod 755 clean.sh" to get run permissions

clear;
make clean TARGET=native
make clean TARGET=sky
make clean TARGET=z1

rm *.native
rm *.sky
rm *.z1

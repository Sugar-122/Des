#!/bin/bash
g++ -o main main.cpp Block.cpp Block.h des.h
./main -e 1.txt 2.txt 1234ABCD
./main -d 2.txt 3.txt 1234ABCD
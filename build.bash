#!/bin/bash -ex

g++-13 -o main.exe main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

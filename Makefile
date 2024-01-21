CC=clang++

DEBUG_CFLAGS= -g -m64 -march=native -std=c++20 -Wall -Wextra
RELEASE_CFLAGS=-O3

LD_FLAGS=-lm -lglfw3 -lGL -lX11 -lpthread

SRC=$(wildcard ./src/*.cpp) $(wildcard ./src/**/*.cpp)
LIB=./include
OBJ=./obj
BIN=./bin

debug:
	$(CC) -c $(SRC) $(DEBUG_CFLAGS) -I $(LIB) || (echo "BUILD FAILED")
	mv *.o $(OBJ) 

build:
	$(CC) $(OBJ)/*.o $(LD_FLAGS) -o $(BIN)/main

run:
	$(BIN)/main

gdb:
	gdb $(BIN)/main

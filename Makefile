
all: main

main: main.cpp
	c++ main.cpp -o main

run: main
	@./main
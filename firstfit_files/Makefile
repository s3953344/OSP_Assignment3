.default: all

all: firstfit

clean:
	rm -rf *.o *.dSYM

firstfit: main.o firstfit.o ../manager.o
	g++ -Wall -Werror -std=c++20 -g -O -o ../$@ $^

# rule for compiling .cpp files
%.o: %.cpp
	g++ -Wall -Werror -std=c++20 -g -O -c $<
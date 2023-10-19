.default: all

all: all

clean:
	rm -rf *.o *.dSYM

best: main.o bestfit.o
	g++ -Wall -Werror -std=c++20 -g -O -o ../$@ $^

# rule for compiling .cpp files
%.o: %.cpp
	g++ -Wall -Werror -std=c++20 -g -O -c $<
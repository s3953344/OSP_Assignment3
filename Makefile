##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##

# provide make targets here to build the two programs

# makefile structure:
# targets (file to make): prerequisites	//needs to exist for commands to work
# 	command
# 	command
# 	etc...

.default: all

all: first best
 
clean:
	rm -rf *.o *.dSYM;
	cd firstfit && $(MAKE) clean;
	cd bestfit && $(MAKE) clean;

	rm -f firstfit;
	rm -f bestfit;


first: ./firstfit/main.o ./firstfit/firstfit.o
	cd firstfit && $(MAKE)

best: ./bestfit/main.o ./firstfit/bestfit.o
	cd bestfit && $(MAKE)
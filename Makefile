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

all: firstfit bestfit
 
clean:
	rm -rf *.o *.dSYM;
	cd firstfit_files && $(MAKE) clean;
	cd bestfit_files && $(MAKE) clean;

	rm -f firstfit;
	rm -f bestfit;


firstfit: ./firstfit_files/main.o ./firstfit_files/firstfit.o manager.o
	cd firstfit_files && $(MAKE)

bestfit: ./bestfit_files/main.o ./bestfit_files/bestfit.o manager.o
	cd bestfit_files && $(MAKE)
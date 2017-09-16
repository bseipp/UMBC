# CMSC 202, Proj4, Cruno
# Date  :  April 16, 2016
# Author:  Brian Seipp
######################################################################

# General macros (like constants, but for a Makefile)
# Use by putting the name in parentheses, with a $ in front
CC     = /usr/local/bin/g++
CFLAGS =  -g -ansi -Wall

# Project-specific macros
# These will need to be updated/changed for each project
PROJ   = proj4
EIGHT = Cruno8.cpp Cruno8.h
SKIP = CrunoSkip.cpp CrunoSkip.h
REVERSE = CrunoReverse.cpp CrunoReverse.h
DRAWTWO = CrunoDraw2.cpp CrunoDraw2.h
CRUNO = CrunoGame.cpp CrunoGame.h
CP = CrunoPlayer.cpp CrunoPlayer.h
GAME   = game.cpp game.h
CARD = card.cpp card.h
PLAYER = player.cpp player.h
DOTOS  = CrunoPlayer.o CrunoDraw2.o Cruno8.o CrunoSkip.o CrunoReverse.o CrunoGame.o game.o player.o card.o proj4.o


# RULES FOR LINKING AND RUNNING EXECUTABLES
######################################################################

# This is the first rule in the file, so typing 
#    only the word "make" will run it by default
all: $(DOTOS)
	$(CC) $(CFLAGS) $(DOTOS)

# Runs the project executable
run: $(PROJ)
	./$(PROJ)

# Runs the project executable via valgrind to check for memory leaks
runV: $(PROJ)
	valgrind ./$(PROJ)


# RULES FOR COMPILATION
######################################################################

CrunoPlayer.o: $(CP)
	$(CC) $(CFLAGS) -c CrunoPlayer.cpp

CrunoDraw2.o: $(DRAWTWO)
	$(CC) $(CFLAGS) -c CrunoDraw2.cpp

Cruno8.o: $(EIGHT) 
	$(CC) $(CFLAGS) -c Cruno8.cpp

CrunoSkip.o: $(SKIP)
	$(CC) $(CFLAGS) -c CrunoSkip.cpp

CrunoGame.o: $(CRUNO) CrunoGame.h Cruno8.h CrunoSkip.h CrunoReverse.h
	$(CC) $(CFLAGS) -c CrunoGame.cpp

CrunoReverse.o: $(REVERSE) CrunoReverse.h
	$(CC) $(CFLAGS) -c CrunoReverse.cpp

game.o: $(GAME) game.h
	$(CC) $(CFLAGS) -c game.cpp

card.o: $(CARD) card.h
	$(CC) $(CFLAGS) -c card.cpp

player.o: $(PLAYER) player.h
	$(CC) $(CFLAGS) -c player.cpp

proj4.o: proj4.cpp Cruno8.o CrunoSkip.o CrunoPlayer.o CrunoDraw2.o CrunoGame.o CrunoReverse.o game.o card.o player.o
	$(CC) $(CFLAGS) -c proj4.cpp


# RULES FOR CLEANING UP EXTRA, UNNECESSARY, AND OLD FILES
######################################################################

# The ".PHONY" tells the Makefile not to look for any dependencies,
#     and to just run the rule immediately
.PHONY: clean cleaner cleanest c

# "clean" removes temporary files (~) and autosaves (#)
clean:
	rm -f *# *~

# "cleaner" removes everything from "clean" along with any .o files
cleaner: clean
	rm -f *.o

# "cleanest" removes everything from "cleaner" along with the executable,
#     any core dump, and any .h.gch files that may have been created
cleanest: cleaner
	rm -f core*; rm -f $(PROJ); rm -f *.h.gch

# "c" is a shortcut for running the "cleanest" rule
c: cleanest


# OTHER RULES 
######################################################################
.PHONY: make
make: Makefile
	emacs Makefile



# PRO-TIP: You can make your own rules!  Anything that you can type in
#     the terminal as a command can be a Makefile rule.  You could have
#     a command to submit your project, a command to open a file for 
#     editing, or anything else you might want to automate!

# One more tip: if you have a very long rule or list of files, you can split
#     it across two (or more) lines by putting a backslash (\) at the end of
#     each line that you want it to continue on from

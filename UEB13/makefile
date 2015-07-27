# Simple Makefive
# Changelog https://onedrive.live.com/redir?page=view&resid=A24EC16A1F3E72AA!4270&authkey=!AFE0aRW5WKEHg3Q
# Andreas Schreiner & Simon Bastian

makefile:
DEL_LIST = *.o *.exe *stackdump

all: build doc
clean:
	rm -f $(DEL_LIST)
build: 
	g++ -c -Wall -pedantic *.cpp
	g++ -o ueb12 *.o
build11: 
	g++ -c -Wall -pedantic *.cpp -std=c++11
	g++ -o ueb12 *.o
doc: 
	/export/home_14/andschreiner/doxygen/bin/doxygen doxyfile
docmac: 
	/Applications/Doxygen/doxygen doxyfile
rebuild: clean all

testbuild: 
	g++ -c *.cpp 
	g++ -o ueb12 *.o
	
testbuild11: 
	g++ -c *.cpp -std=c++11
	g++ -o ueb12 *.o

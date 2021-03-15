CC            = gcc
CXX           = g++
CFLAGS        = -pipe -g -Wall -Wextra -fPIC 
CXXFLAGS      = -pipe -g -std=gnu++1z -Wall -Wextra -fPIC 
SOURCES       = main.cpp \
		block.cpp \
		blockchain.cpp 
OBJECTS       = main.o \
		block.o \
		blockchain.o
Blockchain: $(OBJECTS) 
	$(CXX) -o Blockchain $(OBJECTS) 


all: Blockchain


main.o: main.cpp blockchain.h \
		block.h \
		picosha2.h \
		json.hpp
	$(CXX) -c $(CXXFLAGS) -I. -o main.o main.cpp

block.o: block.cpp block.h \
		picosha2.h
	$(CXX) -c $(CXXFLAGS) -I. -o block.o block.cpp

blockchain.o: blockchain.cpp blockchain.h \
		block.h \
		picosha2.h \
		json.hpp
	$(CXX) -c $(CXXFLAGS) -I.  -o blockchain.o blockchain.cpp

clean: 
	-rm Blockchain
	-rm $(OBJECTS) 

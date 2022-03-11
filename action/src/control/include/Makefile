###############################################################
#
# Purpose: Makefile for "action_editor"
# Author.: robotis
# Version: 0.1
# License: GPL
#
###############################################################

TARGET = action_editor

CXX = g++
INCLUDE_DIRS = -I../../include -I../../../Framework/include  -I../../../../Blackboard/include
CXXFLAGS +=	-O2 -DLINUX -g -Wall -fmessage-length=0 $(INCLUDE_DIRS)
LIBS += -lpthread -lncurses -lrt

DEPN = ../../../../Blackboard/src/blackboard.cpp

OBJS =	./cmd_process.o	\
		./main.o


all: darwin.a $(TARGET)

darwin.a:

$(TARGET): $(OBJS) ../../lib/darwin.a
	$(CXX) -o $(TARGET) $(OBJS) $(DEPN) $(INCLUDE_DIRS) ../../lib/darwin.a $(LIBS)
	
clean:
	rm -f $(OBJS) $(TARGET)






all: findpath

CPP = g++
CPPFLAGS = -O2 -std=c++11

#SRCS = $(shell find -name '*.cpp')
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

findpath: $(OBJS)
	$(CPP) -o findpath $(OBJS)

clean:
	rm -f *.o findpath

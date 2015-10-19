PROGRAM=epollclient
INCLUDES=-I. -I../../src/include
LIBPATH=../../../../../lib/netsvc/0.1.6
SRC_DIRS=.

SRC=$(wildcard $(SRC_DIRS)/%.cpp)

OBJS=$(patsubst %.cpp, %.o, $(wildcard $(SRC_DIRS)/*.cpp))

LIBS:=-lnetsvcd -lpthread -lrt

CXXFLAGS=-static

LEVEL=-D_DEBUG -g 

all: $(OBJS)
	g++ -o $(PROGRAM) ${CXXFLAGS} ${LEVEL} $(OBJS) -L$(LIBPATH) $(LIBS)
$(OBJS): %.o: %.cpp
	g++ -c $(CXXFLAGS) ${LEVEL} ${INCLUDES} $< -o $@

clean:
	rm -rf ${PROGRAM} *.o

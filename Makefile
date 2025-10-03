CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall

all: server client

server: server.cpp logger.h
	$(CXX) $(CXXFLAGS) server.cpp -o server

client: client.cpp logger.h
	$(CXX) $(CXXFLAGS) client.cpp -o client

clean:
	rm -f server client *.o *.log

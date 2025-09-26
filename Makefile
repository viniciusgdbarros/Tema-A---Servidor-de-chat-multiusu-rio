CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall
TARGET = test_logger

all: $(TARGET)

$(TARGET): test_logger.cpp
	$(CXX) $(CXXFLAGS) test_logger.cpp -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
